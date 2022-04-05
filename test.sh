# Cleanup then rebuild
sh clean.sh
sh build.sh

# Run sample test provided
./assign1 < sampleTest/sample01.env > sampleTest/sample01.out
diff --brief --report-identical-files sampleTest/sample01.out sampleTest/sample01.expout

# Test using test cases written by me
# Will loop through all test cases
FolderLocation="TestCases/*.env"
TestCaseFileName="TC"
Count=1
for files in $FolderLocation
do
  ./assign1 <TestCases/$TestCaseFileName$Count.env > TestCases/$TestCaseFileName$Count.out
  diff --brief --report-identical-files TestCases/$TestCaseFileName$Count.out TestCases/$TestCaseFileName$Count.expout
  ((Count=Count+1))
done
