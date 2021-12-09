#' Company : Stevens
#' Project : HW4
#' Purpose : HW4
#' First Name : David
#' Last Name : Fu
#' CWID : 10471854
#' Date : October 20, 2021
#' 
#' 
#' ###### Homework 4 ####
#' 
rm(list=ls())
library(e1071)
library(class) 
set.seed(513)
#'
#'
cancerData=read.csv("C:/Users/Fumonchu/Documents/GitHub/School/CS513/HW3/breast-cancer-wisconsin.csv", header=TRUE)
cancerData$F6 <- as.numeric(cancerData$F6)
cancerData <- cancerData[rowSums(is.na(cancerData)) == 0,]
cancerData <- na.omit(cancerData)
summary(cancerData)
idx<-sort(sample(nrow(cancerData),as.integer(.70*nrow(cancerData))))

training<-cancerData[idx,]

test<-cancerData[-idx,]

nBayes_all <- naiveBayes(Class ~., data = training)

category_all<-predict(nBayes_all,test  )


table(NBayes_all=category_all,Class=test$Class)

NB_wrong<-sum(category_all!=test$Class)

NB_error_rate<-NB_wrong/length(category_all)

rm(list=ls())