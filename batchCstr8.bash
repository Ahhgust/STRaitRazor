# Written by August Woerner
# This is meant as an analog to batchCstr8.bat
#
# It will run strait razor (v3) on standard *nix systems,
# including linux and Mac OSX.

str8="str8rzr"
numcores=1
config="Forenseq.config"

if [ ! -f $config ]; then
    echo "No config file found?!"
    exit
fi

for fq in *.fastq
do
    bn=`basename $fq .fastq`
    mkdir -p $bn/R1
    if [ ! -d $bn/R1 ]; then
        echo "Failed to make directory: $bn/R1"
        exit
    fi  
    ./$str8 -c $config -p $numcores $fq > "$bn/R1/allsequences.txt"
done

for fq in *.fastq.gz
do
    bn=`basename $fq .fastq.gz`
    mkdir -p $bn/R1
    if [ ! -d $bn/R1 ]; then
        echo "Failed to make directory: $bn\R1"
        exit
    fi  
    zcat $fq | ./$str8 -c $config -p $numcores > "$bn/R1/allsequences.txt"
done




