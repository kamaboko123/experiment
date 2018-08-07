#!/usr/bin/python

import sys
import pyjq
import json

if __name__ == "__main__":
    
    json_data = None
    
    json_file = sys.argv[1]
    with open(json_file, "r") as f:
        json_data = json.loads(f.read())
    
    print pyjq.all('.users[] | select (.data.age == 27) | .name', json_data)
    print json.dumps(pyjq.all('.users[] | select (.data.age == 27 and .name=="Seri") | .name', json_data))
    
