for fn in `ls .`; 
do 
	#any folder to exclude add entry here -o means logical or condition
	if [ "$fn" == "HadoopEcoSystemAndMore_InstallationHighLevelSteps.pdf" -o "$fn" == ""renameNumOrder.sh -o "$fn" == "rename.sh" -o "$fn" == "graph" -o "$fn" == "-" ];
	then
		continue
	fi
	nfn=`echo $fn | sed 's/^\([[:alpha:]]*\)\([[:digit:]]\)$/\10\2/g'`
	echo $nfn
	git mv $fn $nfn
done;


