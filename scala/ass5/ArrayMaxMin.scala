import scala.io.StdIn

object ArrayMaxMin {

  def main(args: Array[String]): Unit = {
    print("Enter number of elements: ")
    val n = StdIn.readInt()
    val numbers = new Array[Int](n)
    println("Enter $n elements:")
    for (i <- 0 until n) {
      numbers(i) = StdIn.readInt()
    }

    println("Array: " + numbers.mkString(", "))

    // Finding maximum element
    val maximum = numbers.max

    // Finding minimum element
    val minimum = numbers.min

    println("Maximum element = " + maximum)
    println("Minimum element = " + minimum)
  }
}
}
