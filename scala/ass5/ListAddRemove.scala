
import scala.io.StdIn

object ListAddRemove {

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

    print("Enter element to add 1: ")
    val a = StdIn.readInt()

    print("Enter element to add 2: ")
    val b = StdIn.readInt()

    print("Enter element to add 3: ")
    val c = StdIn.readInt()

    val updatedList = a :: b :: c :: numbers

    println("List after adding 3 elements: " + updatedList)

    // Removing all even numbers
    val finalList = updatedList.filter(_ % 2 != 0)

    println("Final List after removing even numbers: " + finalList)
  }
}

