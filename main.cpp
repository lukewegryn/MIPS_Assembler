/* Luke Wegryn
*  Project1
*  CompOrg 2500
*  2/17/2015
*/
#include <fstream>
#include <iostream>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include <QStringList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QByteArray>

#include "exceptions.h"
#include "lexer.h"
#include "util.h"
#include "helper.cpp"

std::string read_file(const std::string& name) {
  std::ifstream file(name);
  if (!file.is_open()) {
    std::string error = "Could not open file: ";
    error += name;
    throw std::runtime_error(error);
  }
  std::stringstream stream;
  stream << file.rdbuf();
  return std::move(stream.str());
}

/* The parseInstruction takes in the current instruction that the program is
assembling and the file to output the assembly to.
It assembles the current instruction and outputs the value to the
file. */
QByteArray parseInstruction(currentInstruction curr, QString outFile){
    uint assembled = decodeInstruction(curr); //function in helper.cpp
    QFile file(outFile); //file to write the assembled data to
    if (!file.open(QIODevice::Append | QIODevice::Text)) //append data to the file
      return 0;

      QTextStream out(&file);
      uint currMask = 0xf0000000; //this adds zeros to the front to make it appear as 8 characters in the file
      while(!(assembled & currMask)){ //while we still haven't gotten to the first non zero value in the assembled hex
        out << 0; //output a 0 to the text file
        currMask = currMask >> 4; //shift to mask the next hex character
      }
      out << hex << assembled << "\n"; //output the assembled instruction
      return 0;
}

int main(int argc, char** argv) {
  // Adjusting -- argv[0] is always filename.
  --argc;
  ++argv;

  if (argc == 0) {
    std::cerr << "Need a file" << std::endl;
    return 1;
  }

  for (int i = 0; i < argc; ++i) {
    std::string asmName(argv[i]);

    asmName += ".asm";
    
    if (!util::ends_with_subseq(asmName, std::string(".asm"))) {
      std::cerr << "Need a valid file name (that ends in .asm)" << std::endl;
      std::cerr << "(Bad name: " << asmName << ")" << std::endl;
      return 1;
    }

    // 4 is len(".asm")
    auto length = asmName.size() - string_length(".asm");
    std::string baseName(asmName.begin(), asmName.begin() + length);
    QString outFileName;
    outFileName = QString::fromStdString(baseName); //file to write to
    outFileName += ".txt";
    QFile file(outFileName);
    if(file.exists()){
      file.remove();
    }
    std::cout << std::endl;
    try {
      auto text = read_file(asmName);
      try {
		auto lexed = lexer::analyze(text);		// Parses the entire file and returns a vector of instructions

    for (int i =0; i < (int)lexed.size(); i++){ //look through the file and find where all the labels are
      currInstruction.token.clear(); //clear any lingering tokens from my structure
      if(lexed[i].labels.size() > 0){		// Checking if there is a label in the current instruction
        currInstruction.label = QString::fromStdString(lexed[i].labels[0]); //get the current label
        currLabel.first = currInstruction.label; //adding label to symbol table
        currLabel.second = i; //adding location of label to symbol table
        symbolList.append(currLabel); //add the label to the symbol list
        }

    }

    for (int i =0; i < (int)lexed.size(); i++){ //now actually do the assembling
      currInstruction.token.clear(); //clear any lingering tokens
      currInstruction.label.clear(); //clear any lingering labels
      currInstruction.name = QString::fromStdString(lexed[i].name); //get the current instruction name
      std::vector<lexer::token> tokens = lexed[i].args;
      for(int j=0; j < (int)tokens.size(); j++){       // adds all tokens to the dataStructure this instruction like $t1, $t2, $t3
        if (tokens[j].type == lexer::token::Integer){
          int currInt = tokens[j].integer();
          currInstruction.token.append(QString::number(currInt)); //add tokens to current instruction if int
        }
        else
          currInstruction.token.append(QString::fromStdString(tokens[j].string())); //same if string
      }

        currInstruction.position = i; //put the current position in the structure
        currentLineNumber = i+1; //this is for the error messages
        parseInstruction(currInstruction, outFileName); //parse the current instruction and write to file
    }

	  } catch(const bad_asm& e) {
		std::stringstream error;
		error << "Cannot assemble the assembly code at line " << e.line;
		throw std::runtime_error(error.str());
		} catch(const bad_label& e) {
		 std::stringstream error;
		error << "Undefined label " << e.what() << " at line " << e.line;
		throw std::runtime_error(error.str());
		}

    } catch (const std::runtime_error& err) {
      std::cout << err.what() << endl;
      //return 1;
      //return 0;
    }
  }

  return 0;
}
