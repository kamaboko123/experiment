#!/usr/bin/python

import json
import copy
from pprint import pprint

class TemplateEngine:
    _val = {}
    
    def __init__(self, template):
        for k, v in template["variables"].items():
            self._val[k] = v
        
        print self._val
        self.resolve(template["resources"]["r1"])
        
    
    def resolve(self, resource):
        pprint(self._r(resource["data"]))
    
    def _r(self, param):
        print "[_r] %s" % param
        param = copy.deepcopy(param)
        
        if type(param) is dict:
            for k, v in param.items():
                param[k] = self._r(v)
        
        elif type(param) is list:
            if param[0] == "ref":
                if param[1] not in self._val.keys():
                    self._make_val(param[1])
                param = self._val[param[1]]
            else:
                for i in range(len(param)):
                    param[i] = self._r(param[i])
        
        return param
    
    def _make_val(self, name):
        self._val[name] = "new resource"

if __name__ == "__main__":
    
    template = None
    with open("res.json", "r") as f:
        template = json.loads(f.read())
    
    te = TemplateEngine(template)
    
    #print template
    
    
