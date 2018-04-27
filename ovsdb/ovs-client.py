#!/usr/bin/python
#-*- coding: utf-8 -*-

#OVSDB Manipulation library for Python

import socket
import json
import ipaddress
from pprint import pprint

RCV_BUF = 8192

class OvsdbClient:
    
    _ovsdb_ip = None
    _ovsdb_port = None
    
    def __init__(self, ovsdb_port, ovsdb_ip="127.0.0.1"):
        self._ovsdb_ip = ipaddress.ip_address(unicode(ovsdb_ip))
        self._ovsdb_port = int(ovsdb_port)
    
    def _send(self, query):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((str(self._ovsdb_ip), self._ovsdb_port))
        
        s.send(json.dumps(query))
        response = s.recv(8192)
        
        return json.loads(response)
    
    def get_ports(self):
        query = {
            "method":"transact",
            "params":[
                "Open_vSwitch",
                {
                    "op" : "select",
                    "table" : "Port",
                    "where" : [],
                }
            ],
            "id":0
        }
        
        result = self._send(query)
        
        if "error" not in result.keys() or result["error"] is not None:
            raise Exception("なんかのエラー")
        
        ret = {}
        
        for port in result["result"][0]["rows"]:
            #pprint.pprint(port)
            uuid = port["_uuid"][1]
            name = port["name"]
            tag = port["tag"]
            trunks = port["trunks"][1]
            
            if type(tag) is not int:
                tag = []
            
            ret[uuid] = {
                "name" : name,
                "tag" : tag,
                "trunks" : trunks
            }
        
        return ret
    
    def get_bridges(self):
        query = {
            "method":"transact",
            "params":[
                "Open_vSwitch",
                {
                    "op" : "select",
                    "table" : "Bridge",
                    "where" : [],
                }
            ],
            "id":0
        }
        
        result = self._send(query)
        
        if "error" not in result.keys() or result["error"] is not None:
            raise Exception("なんかのエラー")
        
        ret = {}
        
        for br in result["result"][0]["rows"]:
            uuid = br["_uuid"][1]
            name = br["name"]
            
            ports = []
            for port in br["ports"][1]:
                ports.append(port[1])
            
            ret[uuid] = {
                "name" : name,
                "ports" : ports
            }
        
        return ret
    
    def get_bridge_config(self):
        bridges = self.get_bridges()
        ports = self.get_ports()
        
        ret = {}
        
        for br in bridges.values():
            ret[br["name"]] = {
                "ports" : {}
            }
            for port_uuid in br["ports"]:
                ret[br["name"]]["ports"][port_uuid] = ports[port_uuid]
        
        return ret
    
    def get_interface(self):
        query = {
            "method":"transact",
            "params":[
                "Open_vSwitch",
                {
                    "op" : "select",
                    "table" : "Interface",
                    "where" : [],
                }
            ],
            "id":0
        }
        
        result = self._send(query)
        
        pprint(result["result"][0]["rows"])
    
    def add_interface(self):
        query = {
            "method":"transact",
            "params":[
                "Open_vSwitch",
                {
                    "uuid-name" : "test",
                    "op" : "insert",
                    "table" : "Interface",
                    "row":{
                        "name":"enp3s0",
                        "type":""
                    }
                },
                {
                    "uuid-name": "test_p",
                    "op" : "insert",
                    "table" : "Port",
                    "row":{
                        "name" : "enp3s0",
                        "interfaces":[
                            "named-uuid",
                            "test"
                        ],
                        "tag": 222
                    }
                },
                {
                    "where": [
                        [
                            "_uuid",
                            "==",
                            [
                                "uuid",
                                "a950561f-8068-45bb-a25a-83bcd8b3f944"
                            ]
                        ]
                    ],
                    "row": {
                        "ports": [
                            "set",
                            [
                                [
                                    "named-uuid",
                                    "test_p"
                                ],
                                [
                                    "uuid",
                                    "35243057-2ffd-4514-8d03-7b2b2cb05a8e"
                                ],
                                [
                                    "uuid",
                                    "60a408b3-5ac5-4ca6-ae94-d66b092b90e2"
                                ],
                                [
                                    "uuid",
                                    "c43fea7e-9b21-422d-a62f-41048eab1b48"
                                ],
                                [
                                    "uuid",
                                    "f53502df-5695-4a44-8b83-8f73d16d170d"
                                ]
                            ]
                        ]
                    },
                    "op": "update",
                    "table": "Bridge"
                },
                
            ],
            "id":100
        }
        
        pprint(query)
        result = self._send(query)
        
        pprint(result)
    
if __name__ == '__main__':
    ovsdb = OvsdbClient(5678)
    
    ovsdb.add_interface()
