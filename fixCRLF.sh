# Remove CRLF from sample test
cd sampleTest/
dos2unix sample01.expout
cd ..


# Remove CRLF from test cases for m2-3
cd "TestCases/m2-3/"
TestCaseFileName="TC"
Count=1
for files in *.expout
do
  dos2unix $TestCaseFileName$Count.expout
  ((Count=Count+1))
done


# Remove CRLF from test cases for m4
cd ..
cd "m4/"
M4TestCaseFileName="M4_TC"
M4_Count=1
for files in *.expout
do
  dos2unix $M4TestCaseFileName$M4_Count.expout
  ((M4_Count=M4_Count+1))
done