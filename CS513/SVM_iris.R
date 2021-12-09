#  First Name      : Khasha
#  Last Name       : Dehnad
#  Id              : 12345
#  purpose         : Applying SVM to the iris dataset
#                   
rm(list=ls())
data(iris)
View(iris)
# create test and training dataset
index <- seq (1,nrow(iris),by=5)
test<-iris[index,]
training<-iris[-index,]
library(e1071)
?svm()
## svm
svm.model <- svm( Species~ ., data =training  )
svm.pred <- predict(svm.model,  test )

table(actual=test[,5],svm.pred )
SVM_wrong<- (test$Species!=svm.pred)
rate<-sum(SVM_wrong)/length(SVM_wrong)

