import scala.io.StdIn

object FibonacciSeries {

  def fibonacci(n: Int): Unit = {

    var a = 0
    var b = 1

    for (i <- 1 to n) {
      print(a + " ")

      val c = a + b
      a = b
      b = c
    }
  }

  def main(args: Array[String]): Unit = {

    print("Enter the number of terms: ")
    val n = StdIn.readInt()

    println("Fibonacci Series:")
    fibonacci(n)
  }
}
