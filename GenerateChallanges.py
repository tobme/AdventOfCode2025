import os


for x in range(1, 26):
    date = str(x)
    try:
        os.mkdir("AdventOfCode2024/" + date)
    except FileExistsError:
        print(f"Directory '{date}' already exists.")

    hFile = open("AdventOfCode2024/" + date + "/" + date + ".h", "w")
    cppFile = open("AdventOfCode2024/" + date + "/" + date + ".cpp", "w")

    hFile.writelines("#pragma once" + "\n\n")

    hFile.writelines('#include "../IChallenge.h"\n')
    hFile.writelines('#include "../IInput.h"\n')
    hFile.writelines("#include <string>\n#include <memory>\n\n")

    hFile.writelines("class Day" + date + " : public IChallenge\n{\npublic:\n\tDay" + date + "(std::shared_ptr<IInput>& _input);\n\tstd::string runPart1() override;\n\tstd::string runPart2() override;\nprivate:\n\tstd::shared_ptr<IInput> input;\n};")

    hFile.close()

    cppFile.writelines('#include "' + date + '.h"\n\n')

    cppFile.writelines("#include <iostream>\n#include <algorithm>\n\n")

    cppFile.writelines("Day" + date + "::Day" + date + "(std::shared_ptr<IInput>& _input) : input(_input)\n{}\n\n")

    cppFile.writelines("std::string Day" + date + '::runPart1()\n{\n\treturn "";\n}\n\n')
    cppFile.writelines("std::string Day" + date + '::runPart2()\n{\n\treturn "";\n}\n\n')
    cppFile.close()

iChallangeFile = open('AdventOfCode2024/IChallenge.h', "w")

iChallangeFile.writelines("#pragma once\n\n")

iChallangeFile.writelines("#include <string>\n\n")

iChallangeFile.writelines("class IChallenge\n{\npublic:\n\tIChallenge() = default;\n\t virtual ~IChallenge() = default;\n\n\tvirtual std::string runPart1() = 0;\n\tvirtual std::string runPart2() = 0;\n};")

iChallangeFile.close()

challengeSelectorH = open('AdventOfCode2024/ChallengeSelector.h', "w")

challengeSelectorH.writelines("#pragma once\n\n")

challengeSelectorH.writelines('#include "IInput.h"\n')
challengeSelectorH.writelines('#include "IChallenge.h"\n\n')

challengeSelectorH.writelines("#include <memory>\n\n")

challengeSelectorH.writelines("class ChallengeSelector\n{\npublic:\n\tChallengeSelector(const std::string& day, std::shared_ptr<IInput>& _input);\n\n\tstd::string runChallengePart1();\n\tstd::string runChallengePart2();\nprivate:\n\tstd::unique_ptr<IChallenge> challenge;\n};")

challengeSelectorH.close()

challengeSelectorCpp = open('AdventOfCode2024/ChallengeSelector.cpp', "w")

challengeSelectorCpp.writelines('#include "ChallengeSelector.h"\n\n')
challengeSelectorCpp.writelines("#include <iostream>\n#include <chrono>\n#include <memory>\n\n")

for x in range(1,26):
    date = str(x)
    challengeSelectorCpp.writelines('#include "' + date + '/' + date + '.h"\n')

challengeSelectorCpp.writelines("\nstd::unique_ptr<IChallenge> getChallengeFunction(const std::string& day, std::shared_ptr<IInput>& input)\n{\n")

challengeSelectorCpp.writelines('\tif (day == "1")\n\t{\n\t\treturn std::make_unique<Day1>(input);\n\t}\n')

for x in range(2,26):
    challengeSelectorCpp.writelines('\telse if (day == "' + str(x) + '")\n\t{\n\t\treturn std::make_unique<Day' + str(x) + '>(input);\n\t}\n')

challengeSelectorCpp.writelines("\n\treturn nullptr;\n}\n\n")

challengeSelectorCpp.writelines("ChallengeSelector::ChallengeSelector(const std::string& day, std::shared_ptr<IInput>& _input)\n{\n\tchallenge = getChallengeFunction(day, _input);\n}\n\n")

challengeSelectorCpp.writelines("std::string ChallengeSelector::runChallengePart1()\n{\n\treturn challenge->runPart1();\n}\n\n")
challengeSelectorCpp.writelines("std::string ChallengeSelector::runChallengePart2()\n{\n\treturn challenge->runPart2();\n}\n\n")
challengeSelectorCpp.close()