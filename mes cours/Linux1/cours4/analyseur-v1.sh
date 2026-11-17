#!/bin/bash
# Analyse des adresses IP

grep 234 liste-5000-ip-addr.txt > intrusion.txt
grep 114 liste-5000-ip-addr.txt >> intrusion.txt
grep 199 liste-5000-ip-addr.txt >> intrusion.txt
