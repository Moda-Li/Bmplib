#! /bin/bash

COMPILER="g++"
COMPILE_FILE=''

if [ $# -lt 1 ]
then
	echo "parameter error, please input the outfile's name..."
	exit -1;
fi

function ReadAllFileName()
{
    files=`ls`
for filename in $files;do
	
	if [ -d $filename ]
    	then
		#echo  "文件夹 $filename "
	        #递归	
		ReadAllFileName $filename 
			
	else
 
        if [ ${filename##*.} = 'cpp' ] || [ ${filename##*.} = 'c' ]
        then
            #	echo $filename
            COMPILE_FILE=${COMPILE_FILE}" "$filename
        fi
	fi
done	
}

ReadAllFileName
COMPILE_FILE=${COMPILE_FILE#' '} #从左边去掉掉第一个匹配的$substring, ${string#substring}

echo "Start to compile files: $COMPILE_FILE ..."
$COMPILER $COMPILE_FILE -o $1

if [ $? -eq 0 ];
then
	echo "compile success..."
else
	echo "compile failed..."
fi