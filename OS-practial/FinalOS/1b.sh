# Concept & Purpose of the Code
# This shell script implements an address book with options to create, view, insert, delete, modify, and search records. Each record consists of an ID, name, mobile number, salary, and location, which are stored in a text file. This interactive command-line program allows users to manage personal or employee details easily and demonstrates basic file operations and conditional statements in shell scripting.

# Line-by-Line Explanation with Comments

# Display the title "Address Book"
echo -e "Address Book\n"

# Prompt the user to enter the file name for the address book
echo -e "File name:"
read fname  # Read the filename input from the user and store it in fname

# Create the file if it doesn't already exist
touch $fname

# Append headers for each field to the file for clarity
echo -e "id \t name \t mobile_no \t salary \t location \t" >> $fname

# Initialize the choice variable to 0 to start the menu loop
ch=0

# Start a loop that will continue until the user chooses to exit (ch = 7)
while [ $ch -lt 7 ]
do
    # Display the menu options
    echo -e "1) Create Address Book\n"
    echo -e "2) View Address Book\n"
    echo -e "3) Insert a Record\n"
    echo -e "4) Delete a Record\n"
    echo -e "5) Modify a Record\n"
    echo -e "6) Search a Record\n"
    echo -e "7) Exit"

    # Prompt the user to enter their choice
    echo "Enter Your Choice:"
    read ch  # Store the user input in the variable ch

    # Start the case statement to handle each menu option
    case $ch in 
        1)
            # Option 1: Create Address Book
            echo "Enter number of records:"
            read n  # Read the number of records to be added

            # Loop to add each record as specified by the user
            for((i=0;i<$n;i++))
            do
                # Prompt for each field and read values
                echo "Enter id:"
                read id
                
                echo "Enter name:"
                read name
                
                echo "Enter mobile number:"
                read mno

                echo "Enter salary:"
                read sal
                
                echo "Enter location:"
                read loc

                # Append each record to the file with formatting
                echo -e "$id \t $name \t $mno \t $sal \t $loc" >> $fname
            done
        ;;

        2)
            # Option 2: View Address Book
            cat $fname  # Display the entire content of the address book file
        ;;

        3) 
            # Option 3: Insert a New Record
            echo "Enter id:"
            read id
            
            echo "Enter name:"
            read name
            
            echo "Enter mobile number:"
            read mno

            echo "Enter salary:"
            read sal
            
            echo "Enter location:"
            read loc

            # Append the new record to the file
            echo -e "$id \t $name \t $mno \t $sal \t $loc " >> $fname    
        ;;

        4)
            # Option 4: Delete a Record by ID
            echo "Enter Employee ID to delete:"
            read id  # Read the ID to delete

            # Search for the ID in the file
            if grep -w $id $fname
            then
                # If found, delete the record by excluding it from a temporary file
                grep -wv $id $fname >> temp
                rm $fname  # Remove the original file
                mv temp $fname  # Rename the temporary file back to the original filename
            else
                # If ID not found, display message
                echo "record not found"
            fi
        ;;
        
        5)
            # Option 5: Modify a Record by ID
            echo "Enter Employee ID to modify:"
            read id  # Read the ID to modify

           # Search for the ID in the file
            if grep -w $id $fname
            then
                # If found, remove the record to be modified
                grep -wv $id $fname >> temp
                rm $fname
                mv temp $fname  # Save the updated content back to the original file

                # Prompt for new details for the modified record
                echo "Enter e_id:"
                read id

                echo "Enter name:"
                read name

                echo "Enter mobile number:"
                read mno

                echo "Enter salary:"
                read sal
               
                echo "Enter location:"
                read loc

                # Append the modified record back into the file
                echo -e "$id \t $name \t $mno \t $sal \t $loc " >> $fname    
            else
                # If ID not found, display message
                echo "record not found"
            fi
        ;;
        
        6)
            # Option 6: Search for a Record by ID
            echo "Enter Employee id to search:"
            read id  # Read the ID to search for
            if grep -w $id $fname
            then
                # If found, confirm to the user
                echo "Record found"
            else
                # If not found, display message
                echo "record not found"
            fi
        ;;

        7)
            # Option 7: Exit the program
            echo "Exiting the Address Book program"
        ;;

        *)
            # Default case: Invalid option handling
            echo "Invalid choice. Please try again."
        ;;
    esac
done  # End of while loop

# Explanation of Specific Keywords
# touch: Creates a new file if it doesn’t exist or updates the timestamp if it already exists.
# echo -e: Enables special characters like \n (newline) and \t (tab) for formatted output.
# grep: Searches for a specific pattern in a file. -w matches whole words, and -wv excludes lines with the match.
# cat: Concatenates and displays the contents of a file.


# Expected Oral Questions and Answers
# Q: What is the purpose of the touch command in this script?
# A: touch creates the specified file if it doesn’t already exist, allowing us to ensure the address book file is available.

# Q: How does the grep -w command function in this script?
# A: grep -w searches for an exact match of the given word (ID in this case) in the file, ensuring it only returns lines where the full ID is found.

# Q: Why is echo -e used instead of just echo?
# A: echo -e enables the interpretation of special characters like \n for new lines and \t for tabs, allowing formatted output.

# Q: What is the purpose of cat in the View Address Book option?
# A: cat displays the entire content of the address book file, letting the user see all records at once.

# Q: Why is a while loop used with the condition [ $ch -lt 7 ]?
# A: The loop runs the menu continuously until the user chooses option 7 to exit, making it an interactive and repeatable program.
