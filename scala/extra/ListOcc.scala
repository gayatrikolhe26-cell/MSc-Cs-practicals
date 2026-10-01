import scala.io.StdIn

object ListOcc {

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
    for (a <- numbers.distinct) {

    var count = numbers.count(c => c == a)
    print(a+" = "+count+" times 	")
    }
    }
    }

