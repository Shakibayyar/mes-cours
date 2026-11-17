#!/bin/bash
grep -E "$1|$2|$3" liste-5000-ip-addr.txt > intrusion.txt
