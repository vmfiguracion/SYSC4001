README

Goals:
	- To send messages between the administrator and record-keeper.
	- To decode the message to figure out how the data will be handled.
	- To send a response to the client after it has finished the request.
	
Algorithm (pseudo-code):
	- Server (recod-keeper) creates both message queues before any messages will be sent.
	- Client (administrator) sends the data about the employee and what they would like the server to do with the data.
	- Server checks the message key that tells them which action they must do.
		- 1: Insert data into the server
		- 2: Checks employee number for a given name
		- 3: Checks the salary of an employee with a given employee number
		- 4: Return a list of employees working in a given department
		- 5: Deletes the information about the employee with a given employee number
	- Server then sends the information back to the client
		- If it returns 0 an error has occured.
	- This will continue until server ends or client ends.
