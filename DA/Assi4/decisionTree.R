data = read.csv("2010-capitalbikeshare-tripdata.csv")
dim(data)

sapply(data,class)


# #Missing Values 
# data$Age = ifelse(is.na(data$Age),
#                             ave(data$Age, FUN = function(x) mean(x,na.rm=TRUE)),
#                                  data$Age )

data$Member.type = factor(data$Member.type,levels = c('Casual','Member'),labels = c(1,2))
data$Member.type

#Split
library(caTools)
split = sample.split(Y = data$Member.type,SplitRatio = 0.75)
traindata = subset(data,split==TRUE)
testdata = subset(data,split==FALSE)


# install.packages('e1071')
library(rpart)

classifier = rpart(formula = Member.type~ . ,data = traindata[1:500,])
# y_pred = predict(classifier,testdata[,-9])
testdata[,9]
y_pred = predict(classifier,testdata[,-9],type = 'class')
y_pred


cm = table(testdata[,9],y_pred)
cm

plot(classifier)
text(classifier)
install.packages("rpart.plot")
library(rpart.plot)
rpart.plot(classifier)
rpart.plot(classifier,type=4,extra=101)
pred<-predict(fit,newdata=biker_test,type=("class"))
table(biker_test$Member.type,pred)

# library(ElemStatLearn)
# set = traindata
# X1 = seq(min(set[, 1]) - 1, max(set[, 1]) + 1, by = 0.01)
# X2 = seq(min(set[, 2]) - 1, max(set[, 2]) + 1, by = 0.01)
# grid_set = expand.grid(X1, X2)
# colnames(grid_set) = c('Age', 'EstimatedSalary')
# # y_grid = predict(classifier, newdata = grid_set)
# y_grid = y_pred 
# plot(set[, 1:2],
#      main = 'Classifier (Training set)',
#      xlab = 'Age', ylab = 'Estimated Salary',
#      xlim = range(X1), ylim = range(X2))
# contour(X1, X2, matrix(as.numeric(y_grid), length(X1), length(X2)), add = TRUE)
# points(grid_set, pch = '.', col = ifelse(y_grid == 1, 'springgreen3', 'tomato'))
# points(set, pch = 21, bg = ifelse(set[, 3] == 1, 'green4', 'red3'))
