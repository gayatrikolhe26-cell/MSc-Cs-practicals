import scala.io.StdIn
object LeapYear {
  def main(args: Array[String]): Unit = {
    print("enter year you want to check ")
    val year = StdIn.readInt()
    if (year % 400 == 0) {
      println(s"$year is a leap year")
    } else if (year % 100 == 0) {
      println(s"$year is not a leap year")
    } else if (year % 4 == 0) {
      println(s"$year is a leap year")
    } else {
      println(s"$year is not a leap year")
    }
  }
}

