#' Company : Stevens
#' Project : HW3
#' Purpose : HW3
#' First Name : David
#' Last Name : Fu
#' CWID : 10471854
#' Date : October 14, 2021
#' 
#' 
#' ###### Homework 3 ####
#' 
rm(list=ls())
library(kknn)
set.seed(513)
#'
#'
cancerData=read.csv("C:/Users/Fumonchu/Documents/GitHub/School/CS513/HW3/breast-cancer-wisconsin.csv", header=TRUE)
cancerData$F6 <- as.numeric(cancerData$F6)
cancerData <- cancerData[rowSums(is.na(cancerData)) == 0,]
summary(cancerData)
idx<-sort(sample(nrow(cancerData),as.integer(.70*nrow(cancerData))))

training<-cancerData[idx,]

test<-cancerData[-idx,]

predict_k3 <- kknn(formula=Class~., training, test[,-11], k=3, kernel ="rectangular")

fit3 <- fitted(predict_k3)
table(Actual=test$Class,Fitted=fit3)

predict_k5 <- kknn(formula=Class~., training, test[,-11], k=5, kernel ="rectangular")

fit5 <- fitted(predict_k5)
table(Actual=test$Class,Fitted=fit5)

predict_k10 <- kknn(formula=Class~., training, test[,-11], k=10, kernel ="rectangular")

fit10 <- fitted(predict_k10)
table(Actual=test$Class,Fitted=fit10)

rm(list=ls())