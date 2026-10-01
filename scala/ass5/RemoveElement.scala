import scala.io.StdIn

object RemoveElement {

  def main(args: Array[String]): Unit = {

   print("Enter number of elements: ")
    val n = StdIn.readInt()
    var numbers = List[Int]()

    for (i <- 1 to n) {
      print("Enter element " + i + ": ")
      val num = StdIn.readInt()
      numbers = numbers :+ num
}
    println("Original List: " + numbers)

    // Removing element by value
    println("Enter value to remove:")
    val value = StdIn.readInt()

    val removedByValue = numbers.filterNot(_ == value)

    println("List after removing by value: " + removedByValue)

    // Removing element by index
    println("Enter index position to remove:")
    val index = StdIn.readInt()

    if (index >= 0 && index < removedByValue.length) {

      val removedByIndex = removedByValue.patch(index, Nil, 1)

      println("List after removing by index: " + removedByIndex)

    } else {

      println("Invalid index position.")
    }
  }
}

