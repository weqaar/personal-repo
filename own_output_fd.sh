. ' =============================================================================
 |	Week-2:   	Create own output file descriptor 
 |	
 |      Author:		Ahmer Malik
 |     	Language:  	Shell Script
 | 
 |  	Company:  	Techknox Systems
 |     	
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  This script make our own file descriptor "3". Now we can direct our STD-OUT and STD-ERR 
 |		  to "3" with your own specified filename. 
 |	  
 |	 Input:   HANDLE_FILE variable = Path and name where you want to make your fd file.
 |
 |
 |	 Output:  Hello World if it has created the fd succesfully. Otherwise ann error will be shown on you terminal.
 |			
 |   Known Bugs:  There are no known bugs remaining in this program.
 |
 +===========================================================================
'

# The file to which fd=[0,1,2] direct the output
HANDLE_FILE="std_handler"


# Create & set a new output file descriptor 3 for reading.
set_handle_fd(){
	
	#Create a new thread having the same parent using exec() 
	exec 3>$HANDLE_FILE || {

		# if Program fail to create. It will write an error on STDERR.
		echo "$(basename $0):Fail to create a new file desciptor. Exiting" <&2;
		exit 2;
	}
}
close_handle_fd(){

		# It will close the new output fd.
		exec 3>&-;

}


	set_handle_fd;
	# It will write on the new output_fd = std_handler. Hence no ouput shown on the terminal.
	HANDLE_FILE 2>&3;
	echo "Hello World: . . . " 1>&3;

	# It will read the data from std_hadler file.
	echo "Reading data from pipe: "`cat $HANDLE_FILE`;
	close_handle_fd;

 
