import scala.io.StdIn

object SearchArray {

  def main(args: Array[String]): Unit = {

    print("Enter number of elements: ")
    val n = StdIn.readInt()
    val numbers = new Array[Int](n)
    println("Enter $n elements:")
    for (i <- 0 until n) {
      numbers(i) = StdIn.readInt()
    }

    println("Array: " + numbers.mkString(", "))

    // Taking element from user
    println("Enter element to search:")
    val search = StdIn.readInt()

    // Finding index of the element
    val index = numbers.indexOf(search)

    // Checking whether element is present
    if (index != -1) {
      println("Element found at index: " + index)
    } else {
      println("Element not found.")
    }
  }
}
