#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_LISTINGS 1000

// Define the structure to store listing data
typedef struct {
    int id, host_id, minimum_nights, number_of_reviews, calculated_host_listings_count, availability_365;
    char *host_name, *neighbourhood_group, *neighbourhood, *room_type;
    float latitude, longitude, price;
} Listing;

// Function to compare two listings based on host_name
int compareByName(const void *a, const void *b) {
    return strcmp(((Listing*)a)->host_name, ((Listing*)b)->host_name);
}

// Function to compare two listings based on price
int compareByPrice(const void *a, const void *b) {
    return ((Listing*)a)->price - ((Listing*)b)->price;
}

// Function to parse each line in the file and return a listing structure
Listing getFields(char *line) {
    Listing item;
    item.id = atoi(strtok(line, ","));
    item.host_id = atoi(strtok(NULL, ","));
    item.host_name = strdup(strtok(NULL, ","));
    item.neighbourhood_group = strdup(strtok(NULL, ","));
    item.neighbourhood = strdup(strtok(NULL, ","));
    item.latitude = atof(strtok(NULL, ","));
    item.longitude = atof(strtok(NULL, ","));
    item.room_type = strdup(strtok(NULL, ","));
    item.price = atof(strtok(NULL, ","));
    item.minimum_nights = atoi(strtok(NULL, ","));
    item.number_of_reviews = atoi(strtok(NULL, ","));
    item.calculated_host_listings_count = atoi(strtok(NULL, ","));
    item.availability_365 = atoi(strtok(NULL, ","));
    return item;
}

// Function to display a listing structure
void displayStruct(Listing item) {
    printf("Host Name: %s, Price: %.2f\n", item.host_name, item.price);
}

int main() {
    FILE *file = fopen("listings.csv", "r");
    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    Listing listItems[MAX_LISTINGS];
    char line[MAX_LINE_LENGTH];
    int count = 0;

    // Read data from the file and store it in the listItems array
//    while (fgets(line, sizeof(line), file) != NULL && count < MAX_LISTINGS) {
//        listItems[count++] = getFields(line);
//    }


    for(; count < MAX_LISTINGS; count++){
    	if(fgets(line, sizeof(line), file)!= NULL){
    		listItems[count] = getFields(line);
		}
    	
	}


    // Close the file
    fclose(file);

    // Sort the listings by host_name
    qsort(listItems, count, sizeof(Listing), compareByName);

    // Write sorted data to a new file (sorted by name)
    FILE *sortedByNameFile = fopen("sorted_by_name.csv", "w");
    if (sortedByNameFile == NULL) {
        perror("Error opening the file for sorted data by name");
        return 1;
    }

    // Write column headings
    fprintf(sortedByNameFile, "id,host_id,host_name,neighbourhood_group,neighbourhood,latitude,longitude,room_type,price,minimum_nights,number_of_reviews,calculated_host_listings_count,availability_365\n");

	int i = 0;
    //for (; i < count; i++) {
    while(i<count){	
        fprintf(sortedByNameFile, "%d,%d,%s,%s,%s,%.6f,%.6f,%s,%.2f,%d,%d,%d,%d\n",
                listItems[i].id, listItems[i].host_id, listItems[i].host_name,
                listItems[i].neighbourhood_group, listItems[i].neighbourhood,
                listItems[i].latitude, listItems[i].longitude,
                listItems[i].room_type, listItems[i].price,
                listItems[i].minimum_nights, listItems[i].number_of_reviews,
                listItems[i].calculated_host_listings_count, listItems[i].availability_365),
				i++;
    }

    // Close the sorted by name file
    fclose(sortedByNameFile);

    // Sort the listings by price
    qsort(listItems, count, sizeof(Listing), compareByPrice);

    // Write sorted data to a new file (sorted by price)
    FILE *sortedByPriceFile = fopen("sorted_by_price.csv", "w");
    if (sortedByPriceFile == NULL) {
        perror("Error opening the file for sorted data by price");
        return 1;
    }

    // Write column headings
    fprintf(sortedByPriceFile, "id,host_id,host_name,neighbourhood_group,neighbourhood,latitude,longitude,room_type,price,minimum_nights,number_of_reviews,calculated_host_listings_count,availability_365\n");
	i = 0;
//    for (; i < count; i++) {
    while(i<count){
        fprintf(sortedByPriceFile, "%d,%d,%s,%s,%s,%.6f,%.6f,%s,%.2f,%d,%d,%d,%d\n",
                listItems[i].id, listItems[i].host_id, listItems[i].host_name,
                listItems[i].neighbourhood_group, listItems[i].neighbourhood,
                listItems[i].latitude, listItems[i].longitude,
                listItems[i].room_type, listItems[i].price,
                listItems[i].minimum_nights, listItems[i].number_of_reviews,
                listItems[i].calculated_host_listings_count, listItems[i].availability_365),
				i++;
    }

    // Close the sorted by price file
    fclose(sortedByPriceFile);

    return 0;
}