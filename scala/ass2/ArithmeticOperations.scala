import scala.io.StdIn

object ArithmeticOperations {

  def calculate(a: Double, b: Double, operator: Char): Double = {

    operator match {
      case '+' => a + b
      case '-' => a - b
      case '*' => a * b
      case '/' => a / b
      case _   => 0
    }
  }

  def main(args: Array[String]): Unit = {

    print("Enter first number: ")
    val a = StdIn.readDouble()

    print("Enter second number: ")
    val b = StdIn.readDouble()

    print("Enter operator (+, -, *, /): ")
    val operator = StdIn.readChar()

    if (operator == '/' && b == 0)
      println("Division by zero is not allowed")
    else
      println(s"Result = ${calculate(a, b, operator)}")
  }
}
