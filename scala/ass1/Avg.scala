import scala.io.StdIn

object Avg{
  def main(args: Array[String]): Unit = {

    print("Enter n1: ")
    val n1 = scala.io.StdIn.readInt()

    print("Enter n2: ")
    val n2 = scala.io.StdIn.readInt()

    var sum = 0
    var count = 0
    var i = n1

    while (i <= n2) {
      sum = sum + i
      count = count + 1
      i = i + 1
    }

    val average = sum.toDouble / count

    println("Average = " + average)
  }
}

