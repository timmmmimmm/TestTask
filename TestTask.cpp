//The point of the task is to look for correct pairs of braces


#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>


void checkBraces(std::vector<char> input);


int main()
{
	std::ifstream inFile;

	bool legal1 = true, legal2 = true, legal3 = true;   //countermeasure for multiple braces of the same type
	std::vector<char> braces{};
	std::string holder;						//exists just to extract the string from the ifstream

	inFile.open("list.txt");    // input file


	std::cout << "This app looks for matching braces in a  list.txt file." << std::endl <<
		"If you do not have such a file, continue by writing a string and then hitting ENTER" << std::endl;



	if (!inFile.fail()) {

		while (!inFile.eof())
		{
			inFile >> holder;

			for (char character : holder)		//separating the braces in case that other text is present

				if (character == '(' || character == ')' || character == '[' || character == ']' || character == '{' || character == '}')		

					braces.push_back(character);

		}

		inFile.close();
	}
	
	else {
		std::getline(std::cin, holder);

		for (char character : holder)

			if (character == '(' || character == ')' || character == '[' || character == ']' || character == '{' || character == '}')

				braces.push_back(character);
	}

	

	holder.clear();

	checkBraces(braces);

	std::cout << "true" << std::endl;
	return 0;
}


void checkBraces(std::vector<char> input) {

	if (input.empty())	//well if there are no braces than they must match right?
		return;

	std::vector<char>::iterator begin;
	begin = input.begin();					//note to self, iterators are amazing
	char character;						//This is unnecessary but makes the code more readable

	while (begin != input.end())
	{
		character = *begin; //since the opening brace must be always first it is stored

		auto brace1 = begin;
		auto brace2 = std::find(input.begin(), input.end(), character + ((character == '(') ? 1 : 2));  //just some ASCII magic, all braces except for the () ones are two numbers apart so the trenary operator assigns the right value, this spares a lot of unnecessary ifs

		if(brace2 == input.end()) //if the brace is not found
			if (*(brace2 - 1) != character + (character == '(') ? 1 : 2) { //check at the end
				std::cout << "false";
				exit(0); // and if there is not one, than the whole thing is false
			}
				
		input.erase(brace1);

		brace2 = std::find(input.begin(), input.end(), character + ((character == '(') ? 1 : 2)); //This is the downside of vectors i found out, thy move in memory so just to be sure the other element has to be found again (I shold have used another container type)

		input.erase(brace2);

		begin = input.begin();	
	}
}