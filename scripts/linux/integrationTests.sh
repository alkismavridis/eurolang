#1. Define variables
EULC="../../out/eulc"
TARGET_BINARY="../../out/integrationTests/test"
TEST_ROOT_DIR="../../test/test_data/integration_tests"


#2. Locate all tests
TESTS=$(find $TEST_ROOT_DIR -name '*.eul')

#3. Run all tests
SUCCESS=1
for t in $TESTS; do
  #3.a Compile the program and capture the output
  ./compileEul.sh $t $TARGET_BINARY
  ACTUAL_RESULT=$($TARGET_BINARY)

  #3.b Capture the expected result
  EXPECTED_FILE="${t%/*}/expected"
  EXPECTED_RESULT=`cat $EXPECTED_FILE`

  #3.c Check if test passed or not
  if [ "$ACTUAL_RESULT" != "$EXPECTED_RESULT" ]; then
    echo "Test failed: $t"
    echo "      Expected:$EXPECTED_RESULT"
    echo "      Actual:$ACTUAL_RESULT"
    echo ""
    echo ""
    echo ""
    SUCCESS=0
  fi
done


if [ "$SUCCESS" = "1" ];then
  echo "All tests passed"
else
  echo "Some tests did not pass."
fi
