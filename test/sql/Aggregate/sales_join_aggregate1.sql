echo select sales_order_details.productno,description,qtyordered,orderdate from sales_order_details,sales_order,product_master where product_master.productno=sales_order_details.productno and sales_order.orderno=sales_order_details.orderno and orderdate >= '2002-04-01' and orderdate <= '2002-05-31';

select sales_order_details.productno,description,qtyordered from sales_order_details,sales_order,product_master where product_master.productno=sales_order_details.productno and sales_order.orderno=sales_order_details.orderno;

echo select sales_order_details.productno, description, min(qtyordered), max(qtyordered), count(qtyordered), sum(qtyordered) from sales_order_details,sales_order,product_master where product_master.productno=sales_order_details.productno and sales_order.orderno=sales_order_details.orderno  group by sales_order_details.productno,description;

select sales_order_details.productno, description, min(qtyordered), max(qtyordered), count(qtyordered), sum(qtyordered) from sales_order_details,sales_order,product_master where product_master.productno=sales_order_details.productno and sales_order.orderno=sales_order_details.orderno  group by sales_order_details.productno,description;

