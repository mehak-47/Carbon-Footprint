#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Constants for emission factors and conversion rates
#define KG_CO2_PER_KWH_PAKISTAN 0.88
#define KWH_PER_UNIT_ELECTRICITY 1.0
#define KG_CO2_PER_LITER_PETROL 2.32
#define KM_PER_LITER_CAR 10
#define KG_CO2_PER_KG_WASTE 1.85
#define KG_CO2_PER_KM_AIR_TRAVEL 0.2 // Example: 0.2 kg CO2 per km for air travel

// Function prototypes
int get_valid_int(const char *prompt);
int get_valid_fuel_type();
int get_valid_other_fuel_type();
float calculate_electricity_footprint(int units);
float calculate_transportation_footprint(int km, int fuel_type);
float calculate_air_travel_footprint(int km);
float calculate_waste_footprint(int kg);
void provide_feedback(float footprint, int choice);
void show_co2_reduction_tips();

int main() {
    int main_choice;
    char repeat;
	system("color A0");
	
    printf("\t\t\t\t***********************************************************\n");
    printf("\t\t\t\t Welcome to the Carbon Footprint Calculator for Pakistan!\n");
    printf("\t\t\t\t***********************************************************\n\n");

    do {
        // Display the main menu
        printf("Main Menu:\n");
        printf("1. Calculate Carbon Footprint\n");
        printf("2. See CO2 Reduction Tips\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        // Input validation with informative message
        if (scanf("%d", &main_choice) != 1 || (main_choice < 1 || main_choice > 3)) {
            fprintf(stderr, "Invalid choice. Please enter 1, 2, or 3.\n");
            exit(1); // Indicate error
        }

        switch (main_choice) {
            case 1:
                // Calculate carbon footprint
                {
                    int choice, units, km_car, fuel_type, km_air, kg_waste;
                    float carbon_footprint, monthly_footprint = 0.0;

                    // Get user's preferred calculation period
                    printf("\nSelect your preferred timeframe:\n");
                    printf("1. Weekly\n");
                    printf("2. Monthly\n");
                    printf("3. Yearly\n");
                    printf("Enter your choice: ");

                    // Input validation with informative message
                    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
                        fprintf(stderr, "Invalid choice. Please enter 1, 2, or 3.\n");
                        exit(1); // Indicate error
                    }

                    // Calculate carbon footprint based on user's choice
                    carbon_footprint = 0.0f;
                    switch (choice) {
                        case 1: // Weekly
                            printf("\n** Weekly Calculations **\n");
                            units = get_valid_int("Enter your weekly electricity consumption (units): ");
                            carbon_footprint += calculate_electricity_footprint(units);

                            km_car = get_valid_int("Enter the weekly distance you travel by car (km): ");
                            fuel_type = get_valid_fuel_type();
                            carbon_footprint += calculate_transportation_footprint(km_car, fuel_type);

                            km_air = get_valid_int("Enter the weekly distance you travel by air (km): ");
                            carbon_footprint += calculate_air_travel_footprint(km_air);

                            kg_waste = get_valid_int("Enter the weekly amount of waste you generate (kg): ");
                            carbon_footprint += calculate_waste_footprint(kg_waste);
                            break;
                        case 2: // Monthly
                            printf("\n** Monthly Calculations **\n");
                            units = get_valid_int("Enter your monthly electricity consumption (units): ");
                            carbon_footprint += calculate_electricity_footprint(units);

                            km_car = get_valid_int("Enter the monthly distance you travel by car (km): ");
                            fuel_type = get_valid_fuel_type();
                            carbon_footprint += calculate_transportation_footprint(km_car, fuel_type);

                            km_air = get_valid_int("Enter the monthly distance you travel by air (km): ");
                            carbon_footprint += calculate_air_travel_footprint(km_air);

                            kg_waste = get_valid_int("Enter the monthly amount of waste you generate (kg): ");
                            carbon_footprint += calculate_waste_footprint(kg_waste);
                            monthly_footprint = carbon_footprint;
                            break;
                        case 3: // Yearly
                            printf("\n** Yearly Calculations **\n");
                            units = get_valid_int("Enter your yearly electricity consumption (units): ");
                            carbon_footprint += calculate_electricity_footprint(units);

                            km_car = get_valid_int("Enter the yearly distance you travel by car (km): ");
                            fuel_type = get_valid_fuel_type();
                            carbon_footprint += calculate_transportation_footprint(km_car, fuel_type);

                            km_air = get_valid_int("Enter the yearly distance you travel by air (km): ");
                            carbon_footprint += calculate_air_travel_footprint(km_air);

                            kg_waste = get_valid_int("Enter the yearly amount of waste you generate (kg): ");
                            carbon_footprint += calculate_waste_footprint(kg_waste);
                            break;
                    }

                    // Display the calculated footprints and provide feedback
                    printf("\nCarbon Footprint Summary:\n");
                    if (choice == 1) {
                        printf("Weekly: %.2f kg CO2\n", carbon_footprint);
                    } else if (choice == 2) {
                        printf("Monthly: %.2f kg CO2\n", monthly_footprint);
                    } else if (choice == 3) {
                        printf("Yearly: %.2f kg CO2\n", carbon_footprint);
                    }

                    provide_feedback(carbon_footprint, choice);
                }
                break;
            case 2:
                // See CO2 reduction tips
                show_co2_reduction_tips();
                break;
            case 3:
                // Exit
                printf("\nExiting the Carbon Footprint Calculator. Thank you!\n");
                return 0;
            default:
                break;
        }

        // Ask the user if they want to perform another action
        printf("\n\nDo you want to perform another action? (y/n): ");
        scanf(" %c", &repeat);

    } while (repeat == 'y' || repeat == 'Y');

    printf("\nExiting the Carbon Footprint Calculator. Thank you!\n");

    return 0;
}

// Function to calculate air travel footprint based on distance
float calculate_air_travel_footprint(int km) {
    return km * KG_CO2_PER_KM_AIR_TRAVEL;
}

// Function to get a valid integer input from the user
int get_valid_int(const char *prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1 || value < 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n%s", prompt);
        while (getchar() != '\n'); // Clear input buffer
    }
    return value;
}

// Function to get a valid fuel type input from the user
int get_valid_fuel_type() {
    int fuel_type;
    printf("Enter fuel type (1 - Petrol, 2 - CNG, 3 - Other): ");
    while (scanf("%d", &fuel_type) != 1 || (fuel_type < 1 || fuel_type > 3)) {
        fprintf(stderr, "Invalid fuel type. Please enter 1, 2, or 3.\nEnter fuel type (1 - Petrol, 2 - CNG, 3 - Other): ");
        while (getchar() != '\n'); // Clear input buffer
    }
    return fuel_type;
}

// Function to get a valid fuel type input for "Other" category
int get_valid_other_fuel_type() {
    int other_fuel_type;
    printf("Select your fuel type for 'Other':\n");
    printf("1. Electricity\n");
    printf("2. Hybrid Fuel\n");
    printf("3. Biodiesel\n");
    printf("4. Hydrogen Fuel Cells\n");
    printf("5. Solar Power\n");
    printf("Enter your choice: ");
    while (scanf("%d", &other_fuel_type) != 1 || (other_fuel_type < 1 || other_fuel_type > 5)) {
        fprintf(stderr, "Invalid choice. Please enter a number between 1 and 5.\nEnter your choice: ");
        while (getchar() != '\n'); // Clear input buffer
    }
    return other_fuel_type;
}

// Function to calculate electricity footprint based on units consumed
float calculate_electricity_footprint(int units) {
    return units * KG_CO2_PER_KWH_PAKISTAN * KWH_PER_UNIT_ELECTRICITY;
}

// Function to calculate transportation footprint based on distance and fuel type
float calculate_transportation_footprint(int km, int fuel_type) {
    float emission_factor;
    switch (fuel_type) {
        case 1: // Petrol
            emission_factor = KG_CO2_PER_LITER_PETROL;
            break;
        case 2: // CNG
            emission_factor = 2.0;  // Placeholder value for CNG emission factor
            break;
        case 3: // Other
            // Additional cases for other fuel types
            switch (get_valid_other_fuel_type()) {
                case 1: // Electricity
                    emission_factor = 0.3;  // Example: 0.3 kg CO2 per km for electric vehicles
                    break;
                case 2: // Hybrid Fuel
                    emission_factor = 1.5;  // Example: 1.5 kg CO2 per km for hybrid vehicles
                    break;
                case 3: // Biodiesel
                    emission_factor = 2.0;  // Example: 2.0 kg CO2 per km for biodiesel vehicles
                    break;
                case 4: // Hydrogen Fuel Cells
                    emission_factor = 0.2;  // Example: 0.2 kg CO2 per km for hydrogen fuel cell vehicles
                    break;
                case 5: // Solar Power
                    emission_factor = 0.1;  // Example: 0.1 kg CO2 per km for solar-powered vehicles
                    break;
                default:
                    fprintf(stderr, "Invalid choice for 'Other' fuel type.\n");
                    emission_factor = KG_CO2_PER_LITER_PETROL;  // Assuming default emission factor
            }
            break;
        default:
            fprintf(stderr, "Invalid fuel type. Assuming default emission factor.\n");
            emission_factor = KG_CO2_PER_LITER_PETROL;  // Assuming default emission factor for unknown types
    }
    return (km / KM_PER_LITER_CAR) * emission_factor;
}

// Function to calculate waste footprint based on the amount of waste generated
float calculate_waste_footprint(int kg) {
    return kg * KG_CO2_PER_KG_WASTE;
}

// Function to provide feedback based on the total carbon footprint
void provide_feedback(float footprint, int choice) {
    printf("\nFeedback: ");
    switch (choice) {
        case 1: // Weekly
            if (footprint < 5.0) {
                printf("Great job! You're making positive strides in reducing your carbon footprint.");
            } else if (footprint < 15.0) {
                printf("Good effort! There are opportunities to further reduce your carbon footprint.");
            } else {
                printf("Consider making more sustainable choices to reduce your carbon footprint.");
            }
            break;
        case 2: // Monthly
            if (footprint < 20.0) {
                printf("Great job! You're making positive strides in reducing your carbon footprint.");
            } else if (footprint < 50.0) {
                printf("Good effort! There are opportunities to further reduce your carbon footprint.");
            } else {
                printf("Consider making more sustainable choices to reduce your monthly carbon footprint.");
            }
            break;
        case 3: // Yearly
            if (footprint < 200.0) {
                printf("Great job! You're making positive strides in reducing your carbon footprint.");
            } else if (footprint < 500.0) {
                printf("Good effort! There are opportunities to further reduce your carbon footprint.");
            } else {
                printf("Consider making more sustainable choices to reduce your yearly carbon footprint.");
            }
            break;
        default:
            break;
    }
}

// Function to display CO2 reduction tips based on category
void show_co2_reduction_tips() {
    int category_choice;

    // Display the CO2 reduction tips menu
    printf("\nCO2 Reduction Tips Menu:\n");
    printf("1. Electricity Consumption\n");
    printf("2. Transportation\n");
    printf("3. Air Travel\n");
    printf("4. Waste Management\n");
    printf("5. General Tips\n");
    printf("Enter the category number to see detail tips: ");

    // Input validation with informative message
    if (scanf("%d", &category_choice) != 1 || (category_choice < 1 || category_choice > 5)) {
        fprintf(stderr, "Invalid choice. Please enter a number between 1 and 5.\n");
        exit(1); // Indicate error
    }

    // Display detailed tips based on the chosen category
    switch (category_choice) {
        case 1:
            // Electricity Consumption tips
            printf("\n Electricity Consumption:\n");
            printf("1. Use Energy-Efficient Appliances: Choose appliances with the ENERGY STAR label.\n");
            printf("2. Switch to LED Bulbs: They use less energy and last longer than traditional bulbs.\n");
            printf("3. Unplug Devices: Disconnect chargers and electronics when not in use to prevent standby power consumption.\n");
            printf("4. Invest in Renewable Energy: Consider using solar panels or wind turbines to generate clean energy.\n");
            break;
        case 2:
            // Transportation tips
            printf("\n Transportation:\n");
            printf("1. Use Public Transportation: Opt for buses, trains, or subways to reduce individual vehicle emissions.\n");
            printf("2. Carpooling: Share rides with others to reduce the number of vehicles on the road.\n");
            printf("3. Walk or Bike: For short distances, consider walking or cycling instead of using a car.\n");
            printf("4. Choose Fuel-Efficient Vehicles: If possible, select a car with high fuel efficiency or consider electric vehicles.\n");
            printf("5. Maintain Your Vehicle: Regular maintenance improves fuel efficiency.\n");
            break;
        case 3:
            // Air Travel tips
            printf("\n Air Travel:\n");
            printf("1. Choose Direct Flights: Take direct flights when possible, as takeoffs and landings contribute more to emissions.\n");
            printf("2. Pack Light: A lighter plane consumes less fuel.\n");
            printf("3. Offset Carbon Emissions: Consider purchasing carbon offsets for your flights.\n");
            break;
        case 4:
            // Waste Management tips
            printf("\n Waste Management:\n");
            printf("1. Reduce, Reuse, Recycle: Minimize waste by reducing consumption, reusing items, and recycling materials.\n");
            printf("2. Composting: Compost organic waste to reduce the amount of waste sent to landfills.\n");
            printf("3. Choose Sustainable Products: Opt for products with minimal packaging and those made from recycled materials.\n");
            printf("4. Donate or Sell Unwanted Items: Instead of discarding usable items, consider donating or selling them.\n");
            break;
        case 5:
            // General tips
            printf("\n General Tips:\n");
            printf("1. Conserve Water: Use water-saving appliances and be mindful of water usage.\n");
            printf("2. Plant Trees: Trees absorb carbon dioxide and contribute to cleaner air.\n");
            printf("3. Support Sustainable Practices: Choose products and services from companies committed to environmental sustainability.\n");
            printf("4. Educate Yourself: Stay informed about environmental issues and make conscious choices.\n");
            break;
        default:
            break;
    }
}
