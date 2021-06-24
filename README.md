# banks-algorithm

Implementation of the Banker's Algorithm in C

The contents of the input file (data.txt) are described as follows:

- The 1st line tells that there are 3 resources types and 5 processes

- The 2nd line gives the number of resource instances for each resource type: 10 instances for resource type 1, 5 instances for resource type 2, and 7 instances for resource type 3 

- The 3rd to the 5th line give the information of each process:

   - The 1st column is the process name (P0, P1, etc)
   - The 2nd to the 4th columnshows the allocated number instances for each resource type 
      - Example for process P0 
         - 2nd column – 0 instance of resource type 1 
         - 3rd column – 1 instance of resource type 2 
         - 4th column – 0 instance of resource type 3 

   - The 5th to the 7th columnshows the maximum number of instances for each resource type 
      - Example for process P0 
         - 5th column – 7 instances of resource type 1 
         - 6th column – 5 instances of resource type 2 
         - 7th column – 3 instances of resource type 3 
      - Same interpretation goes for Processes P1 to P4 

The input file should be in the same directory as the .c file.
