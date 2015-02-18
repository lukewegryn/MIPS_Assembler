#include <QByteArray>
#include <bitset>
#include <QStringList>
#include <QList>
#include <iostream>
#include <QPair>
#include <QDebug>
#include <exceptions.h>
#include <string>

QPair<QString, int> currLabel; //holds a single label/location combo
QList<QPair<QString, int> > symbolList; //holds all of the label/location combos in a "table"

int currentLineNumber = 0; //current line number for error handling

struct currentInstruction { //current instruction to be assembled
  QString label; //label, if there is one
  QString name; //name of the instruction
  QStringList token; //tokens like registers and offsets
  int position; //current line we are assembling in the file
} currInstruction;

QString rmParen(QString arg){ //remove the parenthases around base of offset
  QString temp;
  temp = arg.remove("(");
  return temp.remove(")");
}

//a string with the register name is passed, and the correct register value is returned
char registerLookup(QString reg){ 

  if(reg == "$zero" || reg == "$0") //just translating using the MIPS green sheet
    return (char)0;
  else if(reg == "$at")
    return (char)1;
  else if(reg == "$v0")
    return (char)2;
  else if(reg == "$v1")
    return (char)3;
  else if(reg == "$a0")
    return (char)4;
  else if(reg == "$a1")
    return (char)5;
  else if(reg == "$a2")
    return (char)6;
  else if(reg == "$a3")
    return (char)7;
  else if(reg == "$t0")
    return (char)8;
  else if(reg == "$t1")
    return (char)9;
  else if(reg == "$t2")
    return (char)10;
  else if(reg == "$t3")
    return (char)11;
  else if(reg == "$t4")
    return (char)12;
  else if(reg == "$t5")
    return (char)13;
  else if(reg == "$t6")
    return (char)14;
  else if(reg == "$t7")
    return (char)15;
  else if(reg == "$s0")
    return (char)16;
  else if(reg == "$s1")
    return (char)17;
  else if(reg == "$s2")
    return (char)18;
  else if(reg == "$s3")
    return (char)19;
  else if(reg == "$s4")
    return (char)20;
  else if(reg == "$s5")
    return (char)21;
  else if(reg == "$s6")
    return (char)22;
  else if(reg == "$s7")
    return (char)23;
  else if(reg == "$t8")
    return (char)24;
  else if(reg == "$t9")
    return (char)25;
  else if(reg == "$k0")
    return (char)26;
  else if(reg == "$k1")
    return (char)27;
  else if(reg == "$gp")
    return (char)28;
  else if(reg == "$sp")
    return (char)29;
  else if(reg == "$fp")
    return (char)30;
  else if(reg == "$ra")
    return (char)31;
  else{ //all of the MIPS registers are listed above so if we get here it means the user put in a bad register
    std::string errMsg = "Cannot assemble the assembly code at line ";
    errMsg.append(std::to_string(currentLineNumber));
    errMsg.append(".");
    errMsg.append("\n");
    throw bad_register(errMsg); //throw a bad register exception
  }
}

//this function is responsible for the R-Type assembly
int rTypeAssemble(unsigned char opcode, unsigned char $rs, unsigned char $rt, unsigned char $rd, unsigned char shamt, unsigned char funct){
    uint assembled = 0x00000000; //start with a blank 32-bit value
    unsigned char lower5BitMask = 0x1f; //these masks are because characters are 8 bit and need to be "trimmed"
    unsigned char lower6BitMask = 0x3f;

    //this is all bit manipulation. I am just stringing together the assembled code using the input values
    assembled = assembled | (opcode << 26); //shift the opcode to the left and add to assembled
    assembled = assembled | (($rs & lower5BitMask) << 21); //we only want to insert the lower 5 bits of $rs
    assembled = assembled | (($rt & lower5BitMask) << 16); 
    assembled = assembled | (($rd & lower5BitMask) << 11);
    assembled = assembled | ((shamt & lower5BitMask) << 6);
    assembled = assembled | ((funct & lower6BitMask) << 0);

    return assembled;
}

//this is very similar to the R-Type, just different parameters/shifts
int iTypeAssemble(unsigned char opcode, unsigned char $rt, unsigned char $rs, unsigned int im){
    uint assembled = 0x00000000; 
    unsigned char lower5BitMask = 0x1f;
    uint lower16BitMask = 0x0000ffff;
    assembled = assembled | ((opcode) << 26);
    assembled = assembled | (($rs & lower5BitMask) << 21);
    assembled = assembled | (($rt & lower5BitMask) << 16);
    assembled = assembled | ((im & lower16BitMask) << 0);


    return assembled;
}

//this should all be pretty self-explanatory.
//I am simply assigning values to registers 
//based on the name/type of instruction and then passing them
//to the correct assembling function above.
int decodeInstruction(currentInstruction curr){ //this is where the instructions are actually assembled
  unsigned char $rd, $rs, $rt, opcode, shamt, funct;
  $rd = $rs = $rt = opcode = shamt = funct = 0x00;
  int immediate;

//r-type instructions
  if(curr.name == "add"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x20;
      shamt = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);
  }

  else if(curr.name == "addu"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x21;
      shamt = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);
  }

  else if(curr.name == "and"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x24;
      shamt = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);
  }

  else if(curr.name == "jr"){
      opcode = 0x00;
      $rs = registerLookup(curr.token.at(0));
      funct = 0x08;
      shamt = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);
  }

  else if(curr.name == "nor"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x27;
      shamt = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);

  }

  else if(curr.name == "or"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x25;
      shamt = 0x00;

    return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);
  }

  else if(curr.name == "slt"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x2a;
      shamt = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);

  }

  else if(curr.name == "sltu"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x2b;
      shamt = 0x00;

  return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);
  }

  else if(curr.name == "sll"){
      bool ok = false;
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rt = registerLookup(curr.token.at(1));
      shamt = (char)curr.token.at(2).toInt(&ok, 10);
      funct = 0x00;
      $rs = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);

  }

  else if(curr.name == "srl"){
      bool ok = false;
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rt = registerLookup(curr.token.at(1));
      shamt = (char)curr.token.at(2).toInt(&ok, 10);
      funct = 0x02;
      $rs = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);

  }

  else if(curr.name == "sub"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x22;
      shamt = 0x00;

      return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);

  }

  else if(curr.name == "subu"){
      opcode = 0x00;
      $rd = registerLookup(curr.token.at(0));
      $rs = registerLookup(curr.token.at(1));
      $rt = registerLookup(curr.token.at(2));
      funct = 0x23;
      shamt = 0x00;

    return rTypeAssemble(opcode, $rs, $rt, $rd, shamt, funct);

  }

//i-Type instructions
  else if(curr.name == "addi"){
    bool ok = false;
    opcode = 0x08;
    $rt = registerLookup(curr.token.at(0));
    $rs = registerLookup(curr.token.at(1));
    immediate = curr.token.at(2).toInt(&ok, 10);

    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "addiu"){
    bool ok = false;
    opcode = 0x09;
    $rt = registerLookup(curr.token.at(0));
    $rs = registerLookup(curr.token.at(1));
    immediate = curr.token.at(2).toInt(&ok, 10);

    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "andi"){
    bool ok = false;
    opcode = 0x0c;
    $rt = registerLookup(curr.token.at(0));
    $rs = registerLookup(curr.token.at(1));
    immediate = curr.token.at(2).toInt(&ok, 10);

    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "beq"){
    bool ok = false;
    opcode = 0x04;
    $rs = registerLookup(curr.token.at(0));
    $rt = registerLookup(curr.token.at(1));
    QString label = curr.token.at(2);
    if(label.toInt(&ok, 10) == 0 && label != "0"){
    for(int i = 0; i < symbolList.size(); i++){
      if(label == symbolList.at(i).first){
            immediate = (symbolList.at(i).second - curr.position - 1);
            return iTypeAssemble(opcode, $rt, $rs, immediate);
          }

    }
    std::string errLabel = label.toUtf8().constData();
    std::string errMsg = "Undefined label \"";
    errMsg.append(errLabel);
    errMsg.append("\" at line ");
    errMsg.append(std::to_string(currentLineNumber));
    errMsg.append(".");
    errMsg.append("\n");
    throw label_not_defined(errMsg);
  }
      immediate = curr.token.at(2).toInt(&ok, 10);
      return iTypeAssemble(opcode, $rt, $rs, immediate);

  }

  else if(curr.name == "bne"){
    bool ok = false;
    opcode = 0x05;
    $rs = registerLookup(curr.token.at(0));
    $rt = registerLookup(curr.token.at(1));
    QString label = curr.token.at(2);
    if(label.toInt(&ok, 10) == 0 && label != "0"){
    for(int i = 0; i < symbolList.size(); i++){
      if(label == symbolList.at(i).first){
            immediate = (symbolList.at(i).second - curr.position - 1);
            return iTypeAssemble(opcode, $rt, $rs, immediate);
          }
    }
    std::string errLabel = label.toUtf8().constData();
    std::string errMsg = "Undefined label \"";
    errMsg.append(errLabel);
    errMsg.append("\" at line ");
    errMsg.append(std::to_string(currentLineNumber));
    errMsg.append(".");
    errMsg.append("\n");
    throw label_not_defined(errMsg);
  }
      immediate = curr.token.at(2).toInt(&ok, 10);
      return iTypeAssemble(opcode, $rt, $rs, immediate);

  }

  else if(curr.name == "lbu"){
    bool ok = false;
    opcode = 0x24;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "lhu"){
    bool ok = false;
    opcode = 0x25;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "ll"){
    bool ok = false;
    opcode = 0x30;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "lui"){
    bool ok = false;
    opcode = 0x0f;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = 0x00;//registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "lw"){
    bool ok = false;
    opcode = 0x23;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "ori"){
    bool ok = false;
    opcode = 0x0d;
    $rt = registerLookup(curr.token.at(0));
    $rs = registerLookup(curr.token.at(1));
    immediate = curr.token.at(2).toInt(&ok, 10);
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "slti"){
    bool ok = false;
    opcode = 0x0a;
    $rt = registerLookup(curr.token.at(0));
    $rs = registerLookup(curr.token.at(1));
    immediate = curr.token.at(2).toInt(&ok, 10);
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "sltiu"){
    bool ok = false;
    opcode = 0x0b;
    $rt = registerLookup(curr.token.at(0));
    $rs = registerLookup(curr.token.at(1));
    immediate = curr.token.at(2).toInt(&ok, 10);
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "sb"){
    bool ok = false;
    opcode = 0x28;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "sc"){
    bool ok = false;
    opcode = 0x38;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "sh"){
    bool ok = false;
    opcode = 0x29;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else if(curr.name == "sw"){
    bool ok = false;
    opcode = 0x2b;
    $rt = registerLookup(curr.token.at(0));
    immediate = curr.token.at(1).toInt(&ok, 10);
    $rs = registerLookup(rmParen(curr.token.at(2)));
    return iTypeAssemble(opcode, $rt, $rs, immediate);
  }

  else{
    std::string errMsg = "Cannot assemble the assembly code at line ";
    errMsg.append(std::to_string(currentLineNumber));
    errMsg.append(".");
    errMsg.append("\n");
    throw bad_instruction(errMsg);
  }

  return 0;
}
