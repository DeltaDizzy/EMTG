def make_missionoptions_source(OptionsDefinitions, now, path = '.'):
    # first load the copyright info
    with open(path + "PyEMTG/OptionsOverhaul/copyright_block.txt", 'r') as file:  # path passed into function = EMTG_path
        copyright_block = file.read()

    with open(path + "src/Core/missionoptions.cpp", "w") as file:
        file.write(copyright_block)

        file.write('//missionoptions class\n')
        file.write('//auto-generated by make_EMTG_missionoptions_journeyoptions.py\n')
        file.write('\n')
        file.write('#include "missionoptions.h"\n')
        file.write('#include "file_utilities.h"\n')
        file.write('#include "EMTG_math.h"\n')
        file.write('\n')
        file.write('#ifdef EMTG_OPTIONS_PYTHON_INTERFACE\n')
        file.write('#include "PyMissionOptions.h"\n')
        file.write('#endif\n')
        file.write('\n')
        file.write('#include <iostream>\n')
        file.write('#include <fstream>\n')
        file.write('#include <sstream>\n')
        file.write('#include <exception>\n')
        file.write('\n')
        file.write('namespace EMTG\n')
        file.write('{\n')

        file.write('    //constructor - just initializes everything\n')
        file.write('    missionoptions::missionoptions()\n')
        file.write('    {\n')

        file.write('        //values\n')
        file.write('        this->Journeys.push_back(EMTG::JourneyOptions()); //default mission has one default journey\n')
        file.write('        this->number_of_journeys = this->Journeys.size();\n')
        file.write('        this->G = 6.674280000000000367e-20;\n')
        file.write('        this->g0 = 9.806649999999999423;\n')
        file.write('        this->AU = 1.49597870691e+8;\n')
        file.write('\n')

        for option in OptionsDefinitions:                
            name = option['name']                          
            dataType = option['dataType']
            scale = ''
            if 'scale' in option:
                if option['scale'] != None:
                    scale = ' * ' + str(option['scale']) + '.0'

            if 'std::vector' in option['dataType']:
                if (len(eval(option['defaultValue'])) > 0):#sometimes an vector option has no default value, which means that it defaults to empty
                    elementType = dataType.replace('std::vector<','').replace('>','')
                    file.write('        this->' + option['name'] + ' = ' + dataType + "({ ")
                    file.write(str(eval(option['defaultValue'])[0]) + scale)
                    for entry in eval(option['defaultValue'])[1:]:
                        file.write(', ' + str(entry) + scale)
                    file.write('}); \n')
            elif option['name'] != 'user_data':                              
                if dataType == 'std::string':
                    file.write('        this->' + name + ' = "' + str(option['defaultValue']).strip('"') + '";\n')
                elif dataType in ['double', 'int', 'size_t']:
                    file.write('        this->' + name + ' = ' + str(option['defaultValue']) + scale + ';\n')
                else:
                    file.write('        this->' + name + ' = (' + dataType + ') ' + str(option['defaultValue']) + ';\n')
                
        file.write('        \n')
        file.write('        //bounds\n')
        
        for option in OptionsDefinitions:
            scale = ''
            if 'scale' in option:
                if option['scale'] != None:
                    scale = ' * ' + str(option['scale']) + '.0'
            if 'std::vector' in option['dataType']:
                elementType = option['dataType'].replace('std::vector<','').replace('>','')
                dataType = option['dataType']                         
                name = option['name']

                bigThing = ''
                mbigThing = ''
                if 'double' in dataType:
                    bigThing = 'math::LARGE'
                    mbigThing = '-math::LARGE'
                elif 'int' in dataType:
                    bigThing = 'INT_MAX'
                    mbigThing = '-INT_MAX'
                elif 'size_t' in dataType:
                    bigThing = 'SIZE_MAX'
                    mbigThing = '-SIZE_MAX'

                if 'std::string' not in option['dataType'] and 'bool' not in option['dataType']:
                    if '[' in str(option['upperBound']) and ']' in str(option['upperBound']):#is this a string containing a list - we need vector bounds
                        lowerBoundVec = option['lowerBound'].replace('[','').replace(']','')
                        lowerBoundCell = lowerBoundVec.split(',')
                        upperBoundVec = option['upperBound'].replace('[','').replace(']','')
                        upperBoundCell = upperBoundVec.split(',')

                        file.write('        this->' + name + '_lowerBound = ' + dataType + "({ ")
                        lowerBound = str(lowerBoundCell[0]).replace('minf', mbigThing)
                        file.write(lowerBound + scale)
                        for entry in lowerBoundCell[1:]:
                            lowerBound = str(entry).replace('minf', mbigThing)
                            file.write(', ' + lowerBound + scale)
                        file.write('}); \n')

                        file.write('        this->' + name + '_upperBound = ' + dataType + "({ ")
                        upperBound = str(upperBoundCell[0]).replace('inf', bigThing)
                        file.write(upperBound + scale)
                        for entry in upperBoundCell[1:]:
                            upperBound = str(entry).replace('inf', bigThing)
                            file.write(', ' + upperBound + scale)
                        file.write('}); \n')

                    else:#scalar bounds for this vector option
                        lowerBound = str(option['lowerBound']).replace('minf', mbigThing)
                        upperBound = str(option['upperBound']).replace('inf', bigThing)
                        if elementType in ['double', 'int', 'size_t']:
                            file.write('        this->' + option['name'] + '_lowerBound = ' + lowerBound + scale + ';\n')
                            file.write('        this->' + option['name'] + '_upperBound = ' + upperBound + scale + ';\n')
                        else: #need to typecast
                            file.write('        this->' + option['name'] + '_lowerBound = (' + elementType + ') ' + lowerBound + scale + ';\n')
                            file.write('        this->' + option['name'] + '_upperBound = (' + elementType + ') ' + upperBound + scale + ';\n')
            else:#scalar option                                   
                name = option['name']                          
                dataType = option['dataType']

                bigThing = ''
                mbigThing = ''
                if 'double' in dataType:
                    bigThing = 'math::LARGE'
                    mbigThing = '-math::LARGE'
                elif 'int' in dataType:
                    bigThing = 'INT_MAX'
                    mbigThing = '-INT_MAX'
                elif 'size_t' in dataType:
                    bigThing = 'SIZE_MAX'
                    mbigThing = '-SIZE_MAX'

                if dataType in ['double', 'int', 'size_t']:
                    lowerBound = str(option['lowerBound']).replace('minf', mbigThing)
                    upperBound = str(option['upperBound']).replace('inf', bigThing)
                    file.write('        this->' + name + '_lowerBound = ' + lowerBound + scale + ';\n')
                    file.write('        this->' + name + '_upperBound = ' + upperBound + scale + ';\n')
                elif 'std::string' not in dataType and 'bool' not in dataType:
                    file.write('        this->' + name + '_lowerBound = (' + dataType + ') ' + str(option['lowerBound']) + scale + ';\n')
                    file.write('        this->' + name + '_upperBound = (' + dataType + ') ' + str(option['upperBound']) + scale + ';\n')
        file.write('    }//end constructor\n')
        file.write('    \n')

        file.write('    missionoptions::missionoptions(std::string optionsfilename) : missionoptions()\n')
        file.write('    {\n')
        file.write('        this->parse_mission(optionsfilename);\n')
        file.write('    }//end constructor with input file\n')
        file.write('    \n')

        file.write('    //parsers\n')
        file.write('    void missionoptions::parse_mission(const std::string& optionsfilename)\n')
        file.write('    {\n')
        file.write('        std::ifstream optionsFileStream;\n')
        file.write('        optionsFileStream.open(optionsfilename);\n')
        file.write('        \n')
        file.write('        if (!optionsFileStream.is_open())\n')
        file.write('        {\n')
        file.write('            throw std::invalid_argument("Cannot find options file: " + optionsfilename);\n')
        file.write('        }\n')
        file.write('        \n')
        file.write('        std::string line;\n')
        file.write('        bool firstJourney = true;\n')
        file.write('        size_t lineNumber = 0;\n')
        file.write('        \n')
        file.write('        while (EMTG::file_utilities::safeGetline(optionsFileStream, line))\n')
        file.write('        {\n')
        file.write('            if (line.size() > 0) //skip blank lines\n')
        file.write('            {\n')
        file.write('                if (line.front() == *"#") //skip comment lines\n')
        file.write('                {\n')
        file.write('                    ++lineNumber;\n')
        file.write('                }\n')  
        file.write('                else if (line == "BEGIN_JOURNEY")\n')
        file.write('                {\n')
        file.write('                    if (firstJourney)\n')
        file.write('                    {\n')
        file.write('                        firstJourney = false;\n')
        file.write('                        this->Journeys.clear();\n')
        file.write('                    };\n')
        file.write('                    \n')
        file.write('                    ++lineNumber;\n')
        file.write('                    this->Journeys.push_back(EMTG::JourneyOptions(optionsFileStream, lineNumber));\n')
        file.write('                }\n')
        file.write('                else\n')
        file.write('                {\n')
        file.write('                    this->parse_line(line, lineNumber);\n')
        file.write('                }\n')
        file.write('            }\n')
        file.write('        }\n')
        file.write('\n')
        file.write('        this->number_of_journeys = this->Journeys.size();\n')
        file.write('\n')
        file.write('        for (EMTG::JourneyOptions& myJourney : this->Journeys)\n')
        file.write('            myJourney.maximum_mass = this->maximum_mass;\n')
        file.write('\n')
        file.write('        this->assemble_initial_guess();\n')
        file.write('    }//end parse_mission()\n')
        file.write('    \n')

        file.write('    void missionoptions::parse_line(const std::string& line, size_t& lineNumber)\n')
        file.write('    {\n')
        file.write('        ++lineNumber;\n')
        file.write('        \n')
        file.write('        std::vector<std::string> linecell;\n')
        file.write('        boost::split(linecell, line, boost::is_any_of(" "), boost::token_compress_on);\n')
        file.write('        \n')

        for option in OptionsDefinitions:
            name = option['name']
            scale = ''
            if 'scale' in option:
                if option['scale'] != None:
                    scale = ' * ' + str(option['scale']) + '.0'

            file.write('        if (linecell[0] == "' + name + '")\n')
            file.write('        {\n')
            #bounds check and assignment
            if 'std::vector' in option['dataType']:
                #length check
                length = str(option['length'])
                if length != 'inf':
                    file.write('            if (linecell.size() - 1 != ' + length + ')\n')
                    file.write('            {\n')
                    file.write('                throw std::invalid_argument("Input option ' + name + ' has been passed " + std::to_string(linecell.size() - 1) + " arguments but requires ' + length + ' arguments.");\n')
                    file.write('            }\n')
                    file.write('            \n')

                dataType = option['dataType']
                elementType = option['dataType'].replace('std::vector<','').replace('>','')
                file.write('            this->' + name + '.clear();\n')
                file.write('            for (size_t entryIndex = 0; entryIndex < linecell.size() - 1; ++entryIndex)\n')
                file.write('            {\n')
                file.write('                this->' + name + '.push_back(')
                if elementType == 'std::string':
                    file.write('linecell[entryIndex + 1]')
                else:
                    if elementType in ['int','size_t']:
                        file.write('std::stoi(linecell[entryIndex + 1])' + scale)
                    elif elementType == 'double':
                        file.write('std::stod(linecell[entryIndex + 1])' + scale)
                    elif elementType == 'bool':
                        file.write('(bool) std::stoi(linecell[entryIndex + 1])')
                    else:
                        print('unknown datatype for option ' + name + '(' + dataType + ')')
                        stop
                file.write(');\n')
                file.write('            }\n')
                
                #bounds check       
                if 'std::string' not in dataType and 'bool' not in dataType: 
                    file.write('            \n')
                    file.write('            //bounds check\n')
                    boundsislist = '[' in str(option['upperBound']) and ']' in str(option['upperBound'])#is this a string containing a list
                    if length != 'inf' and boundsislist:
                            file.write('            for (size_t entryIndex = 0; entryIndex < linecell.size() - 1; ++entryIndex)\n')
                            file.write('            {\n')
                            file.write('               if (this->' + name + '[entryIndex] < this->' + name + '_lowerBound[entryIndex] || this->' + name + '[entryIndex] > this->' + name + '_upperBound[entryIndex])\n')
                            file.write('               {\n')
                            file.write('                   throw std::out_of_range("Input option ' + name + '[" + std::to_string(entryIndex) + "] is out of bounds on line " + std::to_string(lineNumber) + ". Value is " + std::to_string(this->' + name + '[entryIndex]) + ", bounds are [" + std::to_string(this->' + name + '_lowerBound[entryIndex]) + ", " + std::to_string(this->' + name + '_upperBound[entryIndex]) + "].");\n')
                            file.write('               }\n')
                            file.write('            }\n')
                    else: #an array of unknown length
                            file.write('            for (size_t entryIndex = 0; entryIndex < linecell.size() - 1; ++entryIndex)\n')
                            file.write('            {\n')
                            file.write('               if (this->' + name + '[entryIndex] < this->' + name + '_lowerBound || this->' + name + '[entryIndex] > this->' + name + '_upperBound)\n')
                            file.write('               {\n')
                            file.write('                   throw std::out_of_range("Input option ' + name + '[" + std::to_string(entryIndex) + "] is out of bounds on line " + std::to_string(lineNumber) + ". Value is " + std::to_string(this->' + name + '[entryIndex]) + ", bounds are [" + std::to_string(this->' + name + '_lowerBound) + ", " + std::to_string(this->' + name + '_upperBound) + "].");\n')
                            file.write('               }\n')
                            file.write('            }\n')

            else: #any scalar type
                #assign
                if option['name'] == 'user_data':
                    file.write('            if (line != "user_data")\n')
                    file.write('            {\n')
                    file.write('                this->user_data = line;\n')
                    file.write('                this->user_data.erase(this->user_data.begin(), this->user_data.begin() + 10);\n')
                    file.write('            }\n')
                    file.write('            return;\n')
                    file.write('        }\n')
                    continue

                dataType = option['dataType']
                file.write('            this->' + name + ' = ')
                if dataType == 'std::string':
                    file.write('linecell[1];\n')
                else:
                    if dataType in ['int','size_t']:
                        file.write('std::stoi(linecell[1])' + scale + ';\n')
                    elif dataType == 'double':
                        file.write('std::stod(linecell[1])' + scale + ';\n')
                    else: #this is an enum, so we will need to typecast it
                        file.write('(' + option['dataType'] + ') std::stoi(linecell[1]);\n')
                    #bounds check
                    if 'bool' not in dataType:
                        file.write('            \n')
                        file.write('            //bounds check\n')
                        file.write('            if (this->' + name + ' < this->' + name + '_lowerBound || this->' + name + ' > this->' + name + '_upperBound)\n')
                        file.write('            {\n')
                        file.write('                throw std::out_of_range("Input option ' + name + ' is out of bounds on line " + std::to_string(lineNumber) + ". Value is " + std::to_string(this->' + name + ') + ", bounds are [" + std::to_string(this->' + name + '_lowerBound) + ", " + std::to_string(this->' + name + '_upperBound) + "].");\n')
                        file.write('            }\n')
            file.write('            return;\n')
            file.write('        }\n')

        file.write('        \n')
        file.write('        //If we got this far, then the option was not recognized\n')
        file.write('        std::cout << "Option " << linecell[0] << " on line " << lineNumber << " is not recognized. Moving on with life..." << std::endl;\n')
        file.write('    }//end parse_line()\n')
        file.write('    \n')

        file.write('    void missionoptions::write(std::string optionsFileName, const bool& writeAll)\n')
        file.write('    {\n')
        file.write('        std::ofstream optionsFileStream(optionsFileName, std::ios::trunc);\n')
        file.write('        optionsFileStream.precision(20);\n')
        file.write('        \n')
        file.write('        optionsFileStream << "#EMTGv9 .emtgopt file version 2" << std::endl;\n')
        file.write('        optionsFileStream << std::endl;\n')
        file.write('        \n')

        for option in OptionsDefinitions:
            name = option['name']  
            dataType = option['dataType']
            scale = ''
            defaultValue = ''
            if 'scale' in option:
                if option['scale'] != None:
                    scale = ' / ' + str(option['scale']) + '.0'

            if option['name'] == 'user_data':
                file.write('        optionsFileStream << "#' + option['description'] + '" << std::endl;\n')
                file.write('        optionsFileStream << "' + name + ' " << this->' + name + scale + ' << std::endl;\n') 
                file.write('    \n')
            elif 'std::vector' in option['dataType']:
                if (len(eval(option['defaultValue'])) > 0):#sometimes an vector option has no default value, which means that it defaults to empty
                    elementType = dataType.replace('std::vector<','').replace('>','')
                    defaultValue = dataType + "({ "
                    defaultValue += str(eval(option['defaultValue'])[0]) + scale.replace('/','*')
                    for entry in eval(option['defaultValue'])[1:]:
                        defaultValue += ', ' + str(entry) + scale.replace('/','*')
                    defaultValue += '})'
                                        
                    file.write('        if (this->' + name + ' != ' + defaultValue + ' || writeAll)\n')
                    file.write('        {\n')
                    file.write('            optionsFileStream << "#' + option['description'] + '" << std::endl;\n')
                    elementType = option['dataType'].replace('std::vector<','').replace('>','')
                    file.write('            optionsFileStream << "' + name +'";\n')
                    file.write('            for (' + elementType + ' entry : this->' + name + ')\n')
                    file.write('                optionsFileStream << " " << entry' + scale + ';\n')
                    file.write('            optionsFileStream << std::endl;\n')
                    file.write('        }\n')
                    file.write('        \n')
                else:
                    file.write('        optionsFileStream << "#' + option['description'] + '" << std::endl;\n')
                    elementType = option['dataType'].replace('std::vector<','').replace('>','')
                    file.write('        optionsFileStream << "' + name +'";\n')
                    file.write('        for (' + elementType + ' entry : this->' + name + ')\n')
                    file.write('            optionsFileStream << " " << entry' + scale + ';\n')
                    file.write('        optionsFileStream << std::endl;\n')
                    file.write('        \n')
            else:                                              
                if dataType == 'std::string':
                    defaultValue = '"' + str(option['defaultValue']).strip('"') + '"'
                elif dataType in ['double', 'int', 'size_t']:
                    defaultValue = str(option['defaultValue']) + scale.replace('/','*')
                else:
                    defaultValue = str(option['defaultValue'])

                file.write('        if (this->' + name + ' != ' + defaultValue + ' || writeAll)\n')
                file.write('        {\n')
                file.write('            optionsFileStream << "#' + option['description'] + '" << std::endl;\n')
                file.write('            optionsFileStream << "' + name + ' " << this->' + name + scale + ' << std::endl;\n')
                file.write('        }\n')
                file.write('    \n')

        file.write('        optionsFileStream << std::endl;\n')
        file.write('        optionsFileStream << std::endl;\n')
        file.write('    \n')
        file.write('        //write the journeys\n')
        file.write('        optionsFileStream.close();\n')
        file.write('        for (EMTG::JourneyOptions myJourney : this->Journeys)\n')
        file.write('            myJourney.write(optionsFileName, false, writeAll);\n')
        file.write('    }//end write()\n')
        file.write('    \n')

        file.write('    //method to assemble the mission-level initial guess vector\n')
        file.write('    void missionoptions::assemble_initial_guess()\n')
        file.write('    {\n')
        file.write('        this->trialX.clear();\n')
        file.write('        \n')
        file.write('        for (size_t journeyIndex = 0; journeyIndex < this->number_of_journeys; ++journeyIndex)\n')
        file.write('        {\n')
        file.write('            std::tuple<std::string, double> newEntry;\n')
        file.write('            std::string prefix("j" + std::to_string(journeyIndex));\n')
        file.write('            \n')
        file.write('            for (std::tuple<std::string, double>& entry : this->Journeys[journeyIndex].trialX)\n')
        file.write('            {\n')
        file.write('                std::get<0>(newEntry) = prefix + std::get<0>(entry);\n')
        file.write('                std::get<1>(newEntry) = std::get<1>(entry);\n')
        file.write('                this->trialX.push_back(newEntry);\n')
        file.write('            }\n')
        file.write('        }\n')
        file.write('    }//end assemble_initial_guess()\n')


        file.write('}//close namespace EMTG\n')
