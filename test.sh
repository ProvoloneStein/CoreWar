#!/bin/bash
./asm ./champs/42.s
mv ./champs/42.cor ./
./asm ./champs/42.s
./asm 42.cor
./asm 42.s
    if diff 42.cor ./champs/42.cor ; 
		then echo "OK"; 
		else echo "KO"; 
fi