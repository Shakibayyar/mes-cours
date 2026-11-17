#!/bin/bash
PHARE1=$(shuf -n 1 phrase_1.txt)
PHARE2=$(shuf -n 2 phrase_2.txt)
PHARE3=$(shuf -n 1 phrase_3.txt)
PHARE4=$(shuf -n 1 phrase_4.txt)
echo "$PHRASE1 $PHRASE2 $PHRASE3 $PHRASE4"
