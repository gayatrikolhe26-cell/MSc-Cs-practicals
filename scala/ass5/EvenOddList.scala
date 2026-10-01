import scala.io.StdIn
object EvenOddList {

  def main(args: Array[String]): Unit = {

    print("Enter number of elements: ")
    val n = StdIn.readInt()
    val numbers = new Array[Int](n)
    println("Enter n elements:")
    for (i <- 0 until n) {
      numbers(i) = StdIn.readInt()
    }

    println("Array: " + numbers.mkString(", "))

    // Separating even numbers
    val evenNumbers = numbers.filter(_ % 2 == 0).toList

    // Separating odd numbers
    val oddNumbers = numbers.filter(_ % 2 != 0).toList

    println("Even Numbers: " + evenNumbers)
    println("Odd Numbers: " + oddNumbers)
  }
}
