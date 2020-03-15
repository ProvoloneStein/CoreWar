CHAMPS[0]=42
CHAMPS[1]=barriere
CHAMPS[2]=Car
CHAMPS[3]=ex
CHAMPS[4]=Gagnant
CHAMPS[5]=jumper
CHAMPS[6]=maxidef
#!/bin/bash
for element in ${CHAMPS[@]}
do
./asm ./champs/$element.s > /dev/null
mv ./champs/$element.cor ./ > /dev/null
./asm ./champs/$element.s > /dev/null
./asm $element.cor > /dev/null
./asm $element.s > /dev/null
    if diff $element.cor ./champs/$element.cor ;
		then echo "OK $element";
		else echo "KO $element";
fi
done