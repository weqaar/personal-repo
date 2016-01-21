. ' =============================================================================
 |	Week-2:   	Trapping Signals
 |	
 |      Author:		Ahmer Malik
 |     	Language:  	Shell Script
 | 
 |  	Company:  	Techknox Systems
 |     	
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  This scripts continuously prints/write a number in a text file untill it traps signals SIGINT and SIGTERM and ERR.
 |
 |	  Input:   Nothing 
 |
 |
 |	 Output:  Prints numbers with the increment of 1 in a text file "counter.txt" in your home directory.   
 |		  Print "The signal has been trapped!!!" on terminal if SIGINT or SIGTERM interrupterd & then exit
 |		  Print "Error has been trapped!!!!:" with ERR type on terminal, if any command is used wrong.
 |			
 |   Known Bugs:  There are no known bugs remaining in this program.
 |
 +===========================================================================*/
'

trap "echo The signal has been trapped!!!; exit" SIGINT SIGTERM
trap "echo Error has been trapped!!!!: " ERR
echo "pid is $$"
echo $$ > kill_process_ID.txt
i=1
ls-l
while :
do
	sleep 10
	echo $i
	echo $i > counter.txt
	let i=i+1	
done


