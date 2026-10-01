import scala.util.Random

object PerfectNumbers {

  def isPerfect(num: Int): Boolean = {
    var sum = 0

    for (i <- 1 until num if num % i == 0) {
      sum += i
    }

    sum == num
  }

  def main(args: Array[String]): Unit = {

    val random = new Random()

    for (i <- 1 to 5) {
      val num = random.nextInt(100) + 1

      if (isPerfect(num))
        println(s"$num is a Perfect Number")
      else
        println(s"$num is Not a Perfect Number")
    }
  }
}
