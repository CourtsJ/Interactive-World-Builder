/*
A program that sets up a world based on a a file, which contains locations and 
* which locations are directed and by which direction (N,E,S,W)
* The program then takes user input on what direction they want to go in
* and either tells the user it is not possible changes the users location. 
* 
* Courteney Brownie 
* 1 September 2016
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define GRAPH_BUFFER 5
#define LINE_MAX 500
#define N_MAX 1000
#define M_MAX 4000

//global used to assist with directions.
char* compass = "NESW";

typedef struct node_s Node;

struct node_s {
	char location_name[LINE_MAX];
	int directions[4]; //N,E,S,W
};

//Array of Nodes
Node nodePool[N_MAX]; 
int firstFree = 0;

//fills nodePool with given location and sets up directions.
void createNodes(FILE * inputFile, int num_locations){
	char locations[LINE_MAX];
	Node* node = NULL;
	for(int i = 0; i < num_locations; i++){
		node = &nodePool[firstFree];
		fgets(locations,LINE_MAX,inputFile);
		strncpy(node->location_name, locations, LINE_MAX);
		node->directions[0] = -1; //North
		node->directions[1] = -1; //East
		node->directions[2] = -1; //South 
		node->directions[3] = -1; //West
		firstFree += 1;
    }
}

//Checks that user input is either a vaild direction or is the quite value
bool vaildInputCheck(char input) {
	bool vaild = true;
	char valid[] = "NESWQ";
	if (strchr(valid,input)==0){
		vaild = false;
	}
	return vaild;
}

//Assigns values to the node directions based on fileInput.
//Values are keyed to be what node the node is connected to (ie the edge)           
void addDirections(FILE * inputFile, int num_nodes){
	char edges[LINE_MAX];
	int nodeEdge1;
	int nodeEdge2;
	char direction1;
	char direction2;
	for(int i = 0; i < num_nodes; i++){
		fgets(edges,LINE_MAX,inputFile);
		sscanf(edges, "%d %d %c %c", &nodeEdge1, &nodeEdge2, &direction1, &direction2);
		int DirIndex1 = strchr(compass,direction1) - compass;
		int DirIndex2 = strchr(compass,direction2) - compass;
		nodePool[nodeEdge1].directions[DirIndex1] = nodeEdge2;
		nodePool[nodeEdge2].directions[DirIndex2] = nodeEdge1;
	}
}

//Takes user input and prints related "story" information
//aswell as keep track of which location (node) the user is at.
void userAdventure(Node* current_node){
	printf("%s", current_node->location_name);
	bool vaildInput = true;
	char buffer[500];
	int new_direction;
	char input = 0;
	fgets(buffer,500, stdin);
		if(strlen(buffer) != 2){
			vaildInput = false;
		}
		else {
			input = toupper(buffer[0]);	
			vaildInput = vaildInputCheck(input); 
		}
	while (input != 'Q'){
		if (input == 'N' && vaildInput== true){
			if (current_node->directions[0] == -1){
				printf("You can't go North\n");
			} else {
				new_direction = current_node->directions[0];
				current_node = &nodePool[new_direction];
				printf("North to %s", current_node->location_name);
			}
		}
		else if (input == 'E' && vaildInput== true){
			if (current_node->directions[1] == -1){
				printf("You can't go East\n");
			} else {
				new_direction = current_node->directions[1];
				current_node = &nodePool[new_direction];
				printf("East to %s", current_node->location_name);
			}
		}	
		else if (input == 'S' && vaildInput== true){
			if (current_node->directions[2] == -1){
				printf("You can't go South\n");
			}else {
				new_direction = current_node->directions[2];
				current_node = &nodePool[new_direction];
				printf("South to %s", current_node->location_name);
			}
		}
		else if (input == 'W' && vaildInput== true){
			if (current_node->directions[3] == -1){
				printf("You can't go West\n");
			} else {
				new_direction = current_node->directions[3];
				current_node = &nodePool[new_direction];
				printf("West to %s", current_node->location_name);
			}
		}
		vaildInput = true;
		fgets(buffer,LINE_MAX, stdin);
		if(strlen(buffer) != 2){
			vaildInput = false;
		}
		else {
			input = toupper(buffer[0]);	
			vaildInput = vaildInputCheck(input); 
		}
		
	}
	printf("Bye!\n");
}
//Main checks for invaild or missing file. 
//If file is vaild starts reading in file. 
int main(int argc, char* argv[]) {
	if (argc != 2){
		fprintf(stderr, "Missing or invalid world file.\n");
	}
    else { 
		FILE* inputFile = fopen(argv[1], "r");
		if (inputFile == NULL) {
			fprintf(stderr, "Missing or invalid world file.\n");
		}
		else {
			int num_locations;
			int num_edges;
			char graph[GRAPH_BUFFER];
			fgets(graph,GRAPH_BUFFER,inputFile);
			sscanf(graph, "%d %d",&num_locations,&num_edges);
			createNodes(inputFile, num_locations);
			addDirections(inputFile, num_edges);
			Node* current_node = &nodePool[0];
			userAdventure(current_node);
		}
	}
}
