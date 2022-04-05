# Cleanup then rebuild
sh clean.sh
sh build.sh

# Run sample test provided
./assign1 < sampleTest/sample01.env > sampleTest/sample01.out
diff --brief --report-identical-files sampleTest/sample01.out sampleTest/sample01.expout

# Test using test cases written by me
# Will loop through all test cases
FolderLocation="TestCases/m2-3/*.env"
TestCaseFileName="TC"
Count=1
for files in $FolderLocation
do
  ./assign1 <TestCases/m2-3/$TestCaseFileName$Count.env > TestCases/m2-3/$TestCaseFileName$Count.out
  diff --brief --report-identical-files TestCases/m2-3/$TestCaseFileName$Count.out TestCases/m2-3/$TestCaseFileName$Count.expout
  ((Count=Count+1))
done

# Runs tests for milestone 4
echo""
echo "Running Milestone 4 tests"
M4FolderLocation="TestCases/m4/*.env"
M4TestCaseFileName="M4_TC"
M4_Count=1
for files in $M4FolderLocation
do
  ./assign1 <TestCases/m4/$M4TestCaseFileName$M4_Count.env > TestCases/m4/$M4TestCaseFileName$M4_Count.out
  diff --brief --report-identical-files TestCases/m4/$M4TestCaseFileName$M4_Count.out TestCases/m4/$M4TestCaseFileName$M4_Count.expout
  ((M4_Count=M4_Count+1))
done