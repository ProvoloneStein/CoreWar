#!/bin/bash

CHAMP[0]=42
CHAMP[1]=barriere
CHAMP[2]=Car
CHAMP[3]=ex
CHAMP[4]=Gagnant
CHAMP[5]=jumper
CHAMP[6]=maxidef
CHAMP[7]=Octobre_Rouge_V4.2
CHAMP[8]=mortel
CHAMP[9]=slider2
CHAMP[10]=toto


for element in ${CHAMP[@]}
do
echo 'Writing in file $element.cor\n' > t1.txt

./asm ./champs/$element.s > /dev/null
mv ./champs/$element.cor ./test1.cor > /dev/null
./asm_o ./champs/$element.s > /dev/null
mv ./champs/$element.cor ./test2.cor > /dev/null

    if diff test1.cor test2.cor ;
		then echo "OK asm test file $element";
		else echo "KO asm test file $element";
fi
rm test1.cor
rm test2.cor
done

CHAMPS[0]=42
CHAMPS[1]=barriere
CHAMPS[2]=Car
CHAMPS[3]=ex
CHAMPS[4]=Gagnant
CHAMPS[5]=jumper
CHAMPS[6]=maxidef
CHAMPS[7]=Octobre_Rouge_V4.2
CHAMPS[8]=mortel
CHAMPS[9]=slider2
CHAMPS[10]=toto

for element in ${CHAMPS[@]}
do
./asm ./champs/$element.s > /dev/null
mv ./champs/$element.cor ./ > /dev/null
./asm ./champs/$element.s > /dev/null
./asm $element.cor > /dev/null
./asm $element.s > /dev/null
    if diff $element.cor ./champs/$element.cor ;
		then echo "OK dasm test file $element";
		else echo "KO dasm test file $element";
fi
rm $element.cor
rm $element.s
rm ./champs/$element.cor
done