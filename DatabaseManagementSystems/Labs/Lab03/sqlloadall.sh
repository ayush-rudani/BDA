sqlldr data=csv/salesman_master.csv control=ctl/salesman_master.ctl skip=1 bad=salesman_master.bad discard=salesman_master.log
sqlldr data=csv/sales_order.csv control=ctl/sales_order.ctl skip=1 bad=sales_order.bad discard=sales_order.log
sqlldr data=csv/sales_order_details.csv control=ctl/sales_order_details.ctl skip=1 bad=sales_order_details.bad discard=sales_order_details.log
