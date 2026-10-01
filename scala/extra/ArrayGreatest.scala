object ArrayGreatest {

  def main(args: Array[String]): Unit = {
  val arr = Array(58, 27, 100, 24, -5, 2, -6)
  println("orignal array: " + arr.mkString(", "))
  var greatest = -1
  for (i <- arr.length - 1 to 0 by -1) {
      val current = arr(i)
      arr(i) = greatest
      if (current > greatest) {
        greatest = current
      }
    }
    println("Modified array: " + arr.mkString(", "))
  }
}
 
