object ArraySum {

  def main(args: Array[String]): Unit = {
    val A=Array(1,2,3,4,5,6,7,8,9);
    val rutuja=A.sum
    println("total sum by sum()"+rutuja)
    var sum=0
    println("Array: " + A.mkString(", "))
    for(a <-A){
    sum=sum+a
    }
    println("sum by for loop:"+sum)
    }
 }
