import scala.io.StdIn

object MergeLists {

  def main(args: Array[String]): Unit = {

    // Creating two Lists
    val list1 = List(10, 20, 30, 40)
    val list2 = List(30, 40, 50, 60)


    println("List 1: " + list1)
    println("List 2: " + list2)

    // Merging two Lists
    val mergedList = list1 ++ list2
    println("Merged List: " + mergedList)

    // Adding a new element
    println("Enter a new element to add:")
    val newElement = StdIn.readInt()

    val updatedList = mergedList :+ newElement

    println("List after adding new element: " + updatedList)

    // Removing duplicate elements
    val finalList = updatedList.distinct

    println("Final List after removing duplicates: " + finalList)
  }
}
