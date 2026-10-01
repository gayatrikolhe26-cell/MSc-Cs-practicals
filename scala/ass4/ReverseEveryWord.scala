

import scala.io.StdIn

object ReverseEveryWord {
  def main(args: Array[String]): Unit = {

    println("Enter a string:")
    var str = StdIn.readLine()

    
    var words = str.split(" ")


    var result = words.map(word => word.reverse)


    var newString = result.mkString(" ")

    println("Original String = " + str)
    println("After reversing every word = " + newString)
  }
}
