#!/usr/bin/python
#-*- coding: utf-8 -*-

#OVSDB Manipulation library for Python

import socket
import json
import ipaddress
import pprint

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
            tags = port["tag"]
            
            ret[uuid] = {
                "name" : name,
                "tags" : tags
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
        
        for br in bridges.values():
            for br_port in br["ports"]:
                print "%s %s" % (br["name"], ports[br_port])
        

if __name__ == '__main__':
    ovsdb = OvsdbClient(5678)
    
    ovsdb.get_bridge_config()
    
