object SwapNumbers {
  def main(args: Array[String]): Unit = {
    print("Enter first number: ")
    var a = scala.io.StdIn.readInt()
    print("Enter second number: ")
    var b = scala.io.StdIn.readInt()
    println(s"Before swapping: a = $a, b = $b")
    a = a + b
    b = a - b
    a = a - b
    println(s"After swapping: a = $a, b = $b")
  }
}

