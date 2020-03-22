#include "instruction.h"

//Instruction

char* Instr::disassembly()
{
    // sprintf(buffer,"Disassembly is Under Development!!!..............Coming Soon\n");
    return disassemble(this->instr);
}

char* Bicccond(inst x_inst, char* buffer){
	uint32_t cond;
	uint32_t temp;
	uint32_t temp2;
	std::string Bicc[] = {
        "BN", 
        "BE", 
        "BLE", 
        "BL", 
        "BLEU", 
        "BCS", 
        "BNEG", 
        "BVS", 
        "BA", 
        "BNE", 
        "BG", 
        "BGE", 
        "BGU", 
        "BCC", 
        "BPOS", 
        "BVC"
    };
	
	cond = x_inst.format.b.target.branch.cond;
	temp2 = x_inst.format.b.target.branch.disp22 << 2;
	sprintf(buffer," %s \"PC + %08jx\" \n",Bicc[cond].c_str(), (uintmax_t)temp2);
	return buffer;  
}

char* FBfcccond(inst x_inst, char* buffer){
	uint32_t cond;
	uint32_t temp2;

	std::string FBfc[] = {
        "FBN", 
        "FBNE", 
        "FBLG", 
        "FBUL", 
        "FBL", 
        "FBUG", 
        "FBG", 
        "FBU", 
        "FBA", 
        "FBE", 
        "FBUG", 
        "FBGE", 
        "FBGUE", 
        "FBLE", 
        "FBULE", 
        "FBO"
    };

  	cond = x_inst.format.b.target.branch.cond;
	temp2 = x_inst.format.b.target.branch.disp22 << 2;
	sprintf(buffer," %s \"PC + %08jx\" \n",FBfc[cond].c_str(), (uintmax_t)temp2);  
	return buffer;
}

char* CBccccond(inst x_inst, char* buffer){
	uint32_t cond;
	uint32_t temp2;

	std::string cbc[] = {
        "CBN", 
        "CB123", 
        "CB12", 
        "CB13", 
        "CB1", 
        "CB23", 
        "CB2", 
        "CB3", 
        "CBA", 
        "CB0", 
        "CB03", 
        "CB02", 
        "CB023", 
        "CB01", 
        "CB013", 
        "CB012"
    };

  	cond = x_inst.format.b.target.branch.cond;
	temp2 = x_inst.format.b.target.branch.disp22 << 2;
	sprintf(buffer," %s \"PC + %08jx\" \n",cbc[cond].c_str(), (uintmax_t)temp2);  
	return buffer;
}

char* op2(inst x_inst, char* buffer){
	uint32_t op3; 
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs2;
	uint32_t ii;
	int k,l;
	uint32_t opf;
	uint32_t simm13;
	uint32_t op354;
	uint32_t op024;
	std::string RegRd;
	std::string RegRs1;
	std::string RegRs2;
	std::string cbc[][4] = {
						{"ADD"  ,"ADDcc"  ,"TADDcc"    ,"WRASR | WRY"},
					  	{"AND"  ,"ANDcc"  ,"TSUBCC"    ,"WRPSR"},
			 			{"OR"   ,"ORcc"   ,"TADDccTV"  ,"WRWIM"},
		        		{"XOR"  ,"XORcc"  ,"TSUBccTV"  ,"WRTBR"},
		        		{"SUB"  ,"SUBCC"  ,"MULScc"    ,"//FPop1"},
		        		{"ANDN" ,"ANDNcc" ,"SLL"       ,"//FPop2"},
		        		{"ORN"  ,"ORNcc"  ,"SRL"       ," CPop1"},
		        		{"XNOR" ,"XNORcc" ,"SRA"       ,"CPop2"},
		        		{"ADDX" ,"ADDXcc" ,"RDASR|RDY  |STBAR", "JMPL"}, 
		        		{"NULL" ,"NULL"   ,"RDPSR" ,"RETT"},
		        		{"UMUL" ,"UMULcc" ,"RDWIM" ,"Ticc"},
		        		{"SMUL" ,"SMULcc" ,"RDTBR" ,"FLUSH"},
		        		{"SUBX" ,"SUBXcc" ,"NULL"  ,"SAVE"},
		        		{"NULL" ,"NULL"   , "NULL" ,"RESTORE"},
		        		{"UDIV" ,"UDIVcc" ,"NULL"  ,"NULL"},
				        {"SDIV" ,"SDIVcc" ,"NULL"  ,"NULL"}
    };
    rd = x_inst.format.c.rd;
    rs1= x_inst.format.c.rs1;
    op3= x_inst.format.c.op3;
	ii  = x_inst.format.c.operand2.intg.i; 
	

	std::string fpop2[]{
		"51 FCMPs",
		"52 FCMPd",
		"53 FCMPq",
		"55 FCMPEs",
		"56 FCMPEd",
		"57 FCMPEq"
	};

    if(op3==0x34){
    	std::string fpop[] = {
    		"01 FMOVs",
			"05 FNEGs",
			"09 FABSs",
			"29 FSQRTs",
			"2A FSQRTd",
			"2B FSQRTq",
			"41 FADDs",
			"42 FADDd",
			"43 FADDq",
			"45 FSUBs",
			"46 FSUBd",
			"47 FSUBq",
			"49 FMULs",
			"4A FMULd",
			"4B FMULq",
			"4D FDIVs",
			"4E FDIVd",
			"4F FDIVq",
			"69 FsMULd",
			"6E FdMULq",
			"C4 FiTOs",
			"C6 FdTOs",
			"C7 FqTOs",
			"C8 FiTOd",
			"C9 FsTOd",
			"CB FqTOd",
			"CC FiTOq",
			"CD FsTOq",
			"CE FdTOq",
			"D1 FsTOi",
			"D2 FdTOi",
			"D3 FqTOi"
    	};

    	RegRd = "%f";

		

    	k = x_inst.format.c.operand2.fp.opf;
    	// k == 09 is also with the below code
    	if(k==01 || k==05  || k==41 || k==42 || k==43 || k==196 || k==198 || k==199 || k==200 || 
    		k==201 ||k==203 || k==204 || k==205 ||k==206 ||  k==209 || k==210 ||k==211){
    		
    		sprintf(buffer,"%s %s%d %s%d \n",fpop2[k].c_str(),RegRd.c_str(),(rs2),RegRd.c_str(),(rd));
			return buffer;
    	}

			sprintf(buffer,"%s %s%d %s%d %s%d \n",fpop[k].c_str(),RegRd.c_str(),(rd%8),RegRd.c_str(),(rs2%8),RegRd.c_str(),(rs1%8));



    	return buffer;

    }
    else if(op3==0x35){

    	if(rd < 8) RegRd = "%f";
		else if(rd <16) RegRd= "%f";
		else if(rd <24) RegRd= "%f";
		else if(rd <32) RegRd= "%f";

		if(rs1 < 8) RegRs1 = "%f";
		else if(rs1 <16) RegRs1= "%f";
		else if(rs1 <24) RegRs1= "%f";
		else if(rs1 <32) RegRs1= "%f";

		if(rs2 < 8) RegRs2 = "%f";
		else if(rs2 <16) RegRs2= "%f";
		else if(rs2 <24) RegRs2= "%f";
		else if(rs2 <32) RegRs2= "%f";

		sprintf(buffer,"%s %s%d %s%d %s%d \n",fpop2[k].c_str(),RegRd.c_str(),(rd%8),RegRs2.c_str(),(rs2%8),RegRs1.c_str(),(rs1%8));
		
    	return buffer;

    }

    op354 = x_inst.format.c.op3 >> 4;
    op024 = (x_inst.format.c.op3 << 2)>>2;

  	k = op354;
  	l = op024;

  	if(rd < 8) RegRd = "%g";
	else if(rd <16) RegRd= "%o";
	else if(rd <24) RegRd= "%l";
	else if(rd <32) RegRd= "%i";

	if(rs1 < 8) RegRs1 = "%g";
	else if(rs1 <16) RegRs1= "%o";
	else if(rs1 <24) RegRs1= "%l";
	else if(rs1 <32) RegRs1= "%i";

	//excptions
	ii = x_inst.format.c.operand2.intg.i; 
	if(l==0 && k ==3){
		if(rd==0){
			if(ii==0){
				rs2= x_inst.format.c.operand2.intg.rs2.rs2;
				if(rs2 < 8) RegRs2 = "%g";
				else if(rs2 <16) RegRs2= "%o";
				else if(rs2 <24) RegRs2= "%l";
				else if(rs2 <32) RegRs2= "%i";

				sprintf(buffer,"wr %s%d %s%d %s\n",RegRs1.c_str(),(rs1%8),RegRs2.c_str(),(rs2%8),"%y");
			}
			else if(ii==1){
				simm13 = x_inst.format.c.operand2.intg.rs2.simm13;

				if((1) & (simm13 >> 12)){
					simm13 = ((((1<<19)-1)<<12) | simm13);
					sprintf(buffer,"wr %s%d , %x, %s\n",RegRs1.c_str(),(rs1%8), simm13,"%y");
				}
					
				else
					sprintf(buffer,"wr %s%d , %d, %s \n",RegRs1.c_str(),(rs1%8), simm13,"%y");		
			}
		}


		else if(rd>0 && rd <16){
			sprintf(buffer,"Reserved");
		}

		else if(rd>15 && rd <32){
			if(ii==0){
				rs2= x_inst.format.c.operand2.intg.rs2.rs2;
				if(rs2 < 8) RegRs2 = "%g";
				else if(rs2 <16) RegRs2= "%o";
				else if(rs2 <24) RegRs2= "%l";
				else if(rs2 <32) RegRs2= "%i";

				sprintf(buffer,"wr %s%d %s%d %s%d\n",RegRs1.c_str(),(rs1%8),RegRs2.c_str(),(rs2%8),"%asr",(rd));
			}
			else if(ii==1){
				simm13 = x_inst.format.c.operand2.intg.rs2.simm13;

				if((1) & (simm13 >> 12)){
					simm13 = ((((1<<19)-1)<<12) | simm13);
					sprintf(buffer,"wr %s%d , %x, %s%d\n",RegRs1.c_str(),(rs1%8), simm13,"%asr",(rd));
				}
					
				else
					sprintf(buffer,"wr %s%d , %d, %s%d\n",RegRs1.c_str(),(rs1%8), simm13,"%asr",(rd));		
			}
		}
		return buffer;		
	}

	if(l==1 && k==3){
		if(ii==0){
			rs2= x_inst.format.c.operand2.intg.rs2.rs2;
			if(rs2 < 8) RegRs2 = "%g";
			else if(rs2 <16) RegRs2= "%o";
			else if(rs2 <24) RegRs2= "%l";
			else if(rs2 <32) RegRs2= "%i";

			sprintf(buffer,"wr %s%d %s%d %s\n",RegRs1.c_str(),(rs1%8),RegRs2.c_str(),(rs2%8),"%psr");
		}
		else if(ii==1){
			simm13 = x_inst.format.c.operand2.intg.rs2.simm13;

			if((1) & (simm13 >> 12)){
				simm13 = ((((1<<19)-1)<<12) | simm13);
				sprintf(buffer,"wr %s%d , %x, %s \n",RegRs1.c_str(),(rs1%8), simm13,"%psr");
			}
				
			else
				sprintf(buffer,"wr %s%d , %d, %s\n",RegRs1.c_str(),(rs1%8), simm13,"%psr");		
		}
		return buffer;
	}

	if(l==2 && k==3){
		if(ii==0){
			rs2= x_inst.format.c.operand2.intg.rs2.rs2;
			if(rs2 < 8) RegRs2 = "%g";
			else if(rs2 <16) RegRs2= "%o";
			else if(rs2 <24) RegRs2= "%l";
			else if(rs2 <32) RegRs2= "%i";

			sprintf(buffer,"wr %s%d %s%d %s\n",RegRs1.c_str(),(rs1%8),RegRs2.c_str(),(rs2%8),"%wim");
		}
		else if(ii==1){
			simm13 = x_inst.format.c.operand2.intg.rs2.simm13;

			if((1) & (simm13 >> 12)){
				simm13 = ((((1<<19)-1)<<12) | simm13);
				sprintf(buffer,"wr %s%d , %x, %s \n",RegRs1.c_str(),(rs1%8), simm13,"%wim");
			}
				
			else
				sprintf(buffer,"wr %s%d , %d, %s\n",RegRs1.c_str(),(rs1%8), simm13,"%wim");		
		}
		return buffer;
	}

	if(l==1 && k==3){
		if(ii==0){
			rs2= x_inst.format.c.operand2.intg.rs2.rs2;
			if(rs2 < 8) RegRs2 = "%g";
			else if(rs2 <16) RegRs2= "%o";
			else if(rs2 <24) RegRs2= "%l";
			else if(rs2 <32) RegRs2= "%i";

			sprintf(buffer,"wr %s%d %s%d %s\n",RegRs1.c_str(),(rs1%8),RegRs2.c_str(),(rs2%8),"%tbr");
		}
		else if(ii==1){
			simm13 = x_inst.format.c.operand2.intg.rs2.simm13;

			if((1) & (simm13 >> 12)){
				simm13 = ((((1<<19)-1)<<12) | simm13);
				sprintf(buffer,"wr %s%d , %x, %s \n",RegRs1.c_str(),(rs1%8), simm13,"%tbr");
			}
				
			else
				sprintf(buffer,"wr %s%d , %d, %s\n",RegRs1.c_str(),(rs1%8), simm13,"%tbr");		
		}
		return buffer;
	}
	// RDY and RDASR
	if(op3==0x28){
		if(rs1==0){
			if(ii==0){
				rs2= x_inst.format.c.operand2.intg.rs2.rs2;
				if(rs2 < 8) RegRs2 = "%g";
				else if(rs2 <16) RegRs2= "%o";
				else if(rs2 <24) RegRs2= "%l";
				else if(rs2 <32) RegRs2= "%i";

				sprintf(buffer,"rd %s %s%d\n","%y",RegRd.c_str(),(rd%8));
			}
			else if(ii==1){
				simm13 = x_inst.format.c.operand2.intg.rs2.simm13;

				if((1) & (simm13 >> 12)){
					simm13 = ((((1<<19)-1)<<12) | simm13);
					sprintf(buffer,"rd %s , %s%d \n","%y",RegRd.c_str(),(rd%8));
				}
					
				else
					sprintf(buffer,"wr %s %s%d %x\n","%y",RegRd.c_str(),(rd%8), simm13);		
			}
		}


		else if(rd>0 && rd <16){
			if(ii==0){
				rs2= x_inst.format.c.operand2.intg.rs2.rs2;
				if(rs2 < 8) RegRs2 = "%g";
				else if(rs2 <16) RegRs2= "%o";
				else if(rs2 <24) RegRs2= "%l";
				else if(rs2 <32) RegRs2= "%i";

				sprintf(buffer,"wr %s%d %s%d %s%d\n",RegRs1.c_str(),(rs1%8),RegRs2.c_str(),(rs2%8),"%asr",(16+rd));
			}
			else if(ii==1){
				simm13 = x_inst.format.c.operand2.intg.rs2.simm13;

				if((1) & (simm13 >> 12)){
					simm13 = ((((1<<19)-1)<<12) | simm13);
					sprintf(buffer,"wr %s%d , %x, %s%d\n",RegRs1.c_str(),(rs1%8), simm13,"%asr",(16+rd));
				}
					
				else
					sprintf(buffer,"wr %s%d , %d, %s%d\n",RegRs1.c_str(),(rs1%8), simm13,"%asr",(16+rd));		
			}
		}

		else if(rs1>15 && rs1 <32){
			if(ii==0){
				rs2= x_inst.format.c.operand2.intg.rs2.rs2;
				if(rs2 < 8) RegRs2 = "%g";
				else if(rs2 <16) RegRs2= "%o";
				else if(rs2 <24) RegRs2= "%l";
				else if(rs2 <32) RegRs2= "%i";

				sprintf(buffer,"wr %s%d %s%d %s%d\n",RegRs1.c_str(),(rs1%8),RegRs2.c_str(),(rs2%8),"%asr",(rd));
			}
			else if(ii==1){
				simm13 = x_inst.format.c.operand2.intg.rs2.simm13;

				if((1) & (simm13 >> 12)){
					simm13 = ((((1<<19)-1)<<12) | simm13);
					sprintf(buffer,"wr %s%d , %x, %s%d\n",RegRs1.c_str(),(rs1%8), simm13,"%asr",(rd));
				}
					
				else
					sprintf(buffer,"wr %s%d , %d, %s%d\n",RegRs1.c_str(),(rs1%8), simm13,"%asr",(rd));		
			}
		}
	}

	if(ii==0){
		 rs2= x_inst.format.c.operand2.intg.rs2.rs2;
	  	if(rs2 < 8) RegRs2 = "%g";
		else if(rs2 <16) RegRs2= "%o";
		else if(rs2 <24) RegRs2= "%l";
		else if(rs2 <32) RegRs2= "%i";

		sprintf(buffer,"%s %s%d %s%d %s%d i= %d\n",cbc[l][k].c_str(),RegRs1.c_str(),(rs1%8),RegRs2.c_str(),(rs2%8),RegRd.c_str(),(rd%8),ii);
	}
	else if(ii==1){
		simm13 = x_inst.format.c.operand2.intg.rs2.simm13;

		if((1) & (simm13 >> 12)){
			simm13 = ((((1<<19)-1)<<12) | simm13);
			sprintf(buffer,"%s %s%d , %x, %s%d \n",cbc[l][k].c_str(),RegRs1.c_str(),(rs1%8), simm13,RegRd.c_str(),(rd%8));
		}
        	
		else
			sprintf(buffer,"%s %s%d , %d, %s%d \n",cbc[l][k].c_str(),RegRs1.c_str(),(rs1%8), simm13,RegRd.c_str(),(rd%8));		
	}
    return buffer;
}

char* op3one(inst x_inst, char* buffer){
	uint32_t op3; 
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs2;
	uint32_t ii;
	int k,l;
	uint32_t opf;
	uint32_t simm13;
	uint32_t op354;
	uint32_t op024;
	std::string RegRd;
	std::string RegRs1;
	std::string RegRs2;
	std::string cbc[][4] = {
						{"LD"    ,"LDA"    ,"LDF"   ,"LDC"},
					  	{"LDUB"  ,"LDUBA"  ,"LDFSR" ,"LDCSR"},
			 			{"LDUH"  ,"LDUHA"  ,"NULL"  ,"NULL"},
		        		{"LDD"   ,"LDDA"   ,"LDDF"  ,"LDDC"},
		        		{"ST"    ,"STA"    ,"STF"   ,"STC"},
		        		{"STB"   ,"STBA"   ,"STFSR" ,"STCSR"},
		        		{"STH"   ,"STHA"   ,"STDFQ" ," STDCQ"},
		        		{"STD"   ,"STDA"   ,"STDF"  ,"STDC"},
		        		{"NULL"  ,"NULL"   ,"NULL"  , "NULL"}, 
		        		{"LDSB"  ,"LDSBA"  ,"NULL"  ,"NULL"},
		        		{"LDSH"  ,"LDSHA"  ,"NULL"  ,"NULL"},
		        		{"NULL"  ,"NULL"   ,"NULL"  ,"NULL"},
		        		{"NULL"  ,"NULL"   ,"NULL"  ,"NULL"},
		        		{"LDSTUB","LDSTUBA","NULL"  ,"NULL"},
		        		{"NULL"  ,"NULL"   ,"NULL"  ,"NULL"},
				        {"SWAP"  ,"SWAPA"  ,"NULL"  ,"NULL"}
    };
    rd = x_inst.format.c.rd;
    rs1= x_inst.format.c.rs1;
    op3= x_inst.format.c.op3;
	ii  = x_inst.format.c.operand2.intg.i; 

    op354 = x_inst.format.c.op3 >> 4;
    op024 = (x_inst.format.c.op3 << 2)>>2;

  	k = op354;
  	l = op024;

  	if(rd < 8) RegRd = "%g";
	else if(rd <16) RegRd= "%o";
	else if(rd <24) RegRd= "%l";
	else if(rd <32) RegRd= "%i";

	if(rs1 < 8) RegRs1 = "%g";
	else if(rs1 <16) RegRs1= "%o";
	else if(rs1 <24) RegRs1= "%l";
	else if(rs1 <32) RegRs1= "%i";

	ii  = x_inst.format.c.operand2.intg.i; 
	sprintf(buffer,"ii= %d\n", ii);
	if(ii==0){
		 rs2= x_inst.format.c.operand2.intg.rs2.rs2;
	  	if(rs2 < 8) RegRs2 = "%g";
		else if(rs2 <16) RegRs2= "%o";
		else if(rs2 <24) RegRs2= "%l";
		else if(rs2 <32) RegRs2= "%i";

		sprintf(buffer,"%s [%s%d + %s%d], %s%d \n i=%d",cbc[l][k].c_str(),RegRs1.c_str(),(rs1%8),RegRs2.c_str(),(rs2%8),RegRd.c_str(),(rd%8),ii);
	}
	else if(ii==1){
		simm13 = x_inst.format.c.operand2.intg.rs2.simm13;

		if((1) & (simm13 >> 12)){
			simm13 = ((((1<<19)-1)<<12) | simm13);
			sprintf(buffer,"%s [%s%d + %x], %s%d \n",cbc[l][k].c_str(),RegRs1.c_str(),(rs1%8), simm13,RegRd.c_str(),(rd%8));
		}
        	
		else
			sprintf(buffer,"%s [%s%d + %d], %s%d \n",cbc[l][k].c_str(),RegRs1.c_str(),(rs1%8), simm13,RegRd.c_str(),(rd%8));		
	}
    return buffer;
}



char* disassemble(inst x_inst) {
	uint32_t r;		// random which will be used to store some imp values
	uint32_t eop;	//extra opcode like op2 and op3
	uint32_t temp;
	uint32_t temp2;
	std::string reg;

	std::string dissassmbly;
	char* buffer = new char [100];

	switch(x_inst.op){
		case 1:
			
			//sprintf(buffer,"we are in opcode1\n");
			r = x_inst.format.a.disp30 << 2;
			sprintf(buffer,"call \"PC + %08jx\" \n", (uintmax_t)r);
			break;


		case 0:
			//sprintf(buffer,"we are in opcode0\n");
			eop = x_inst.format.b.op2;
			if (eop ==0 || eop == 1 || eop == 3 || eop == 5)
			{
				sprintf(buffer,"ERROR!!! Unidentified Argument while reading OPCODE2");
			}
			else if(eop == 2){
				//sprintf(buffer,"We have to write for Bicc\n");
				r = x_inst.format.b.target.branch.disp22 << 2;
				temp2 = x_inst.format.b.target.branch.cond;
				temp  = x_inst.format.b.target.branch.a << 2;
				Bicccond(x_inst,buffer);
			}

			else if (eop == 4)
			{
				r = x_inst.format.b.target.sethi.imm22 << 2;
				temp = x_inst.format.b.target.sethi.rd;
				if(temp < 8) reg = "%g";
				else if(temp <16) reg= "%o";
				else if(temp <24) reg= "%l";
				else if(temp <32) reg= "%i";
				sprintf(buffer,"sethi %chi(%08jx), %s%d \n",'%',(uintmax_t)r,reg.c_str(),(temp%8));
			}

			else if(eop == 6){
				FBfcccond(x_inst,buffer);
			}

			else if(eop == 7){
				CBccccond(x_inst,buffer);
			}

			break;

		case 2:
			eop = x_inst.format.c.op3 >> 4; //getting op3[5:4]
			op2(x_inst,buffer);
			break;


		case 3:
			//sprintf(buffer,"we are in opcode 2 or 3\n");
			eop = x_inst.format.c.op3 >> 4;
			op3one(x_inst,buffer);
			break;


        default:
            //cerr << "OPCODE length changed (not 2-bits anymore)?" << endl;
            exit(1);		

	}
	return buffer;
}