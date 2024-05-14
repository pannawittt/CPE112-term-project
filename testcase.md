# TEST CASE
### main node of our bus stop(s)
![Alt text](src/img/scopes.png)

### to easier understand i'll draw a node on the map the arrow represent the main road that may have the routes

## Dynamic of Bus in user's time
- src-dest ที่เดียวกัน แต่โปรแกรมควรแนะนำให้ใช้เส้นทางที่มีรถในขณะนั้น
  
## หา path แบบไม่กำหนดผู้เดินรถ
- src-dest ไม่มีสายไหนผ่าน → ไม่ต้องตอบ
- src-dest มี 1 สายผ่าน → ตอบสายที่มาก่อน
- src-dest มีมากกว่า 1 สายผ่าน (ต้องต่อรถ) → ตอบสายที่ใช้เวลาจาก src-dest รวมถึงเวลารอน้อยกว่าก่อน
  
## หา path แบบกำหนดผู้เดินรถ
- src-dest ไม่มีสายไหนผ่าน → ไม่ต้องตอบ
- src-dest มีสายของบริษัทอื่นผ่าน → ไม่ต้องตอบ
- src-dest มี 1 สายผ่าน → ตอบสายที่มาก่อน
- src-dest มีมากกว่า 1 สาย → ตอบสายที่ใช้เวลาจาก - src-dest รวมถึงเวลารอน้อยกว่าก่อนโดยที่ต้องเป็นสายที่อยู่ในบริษัทเดียวกัน
  
## หาป้าย interchange ของแต่ละสาย
- แสดงป้ายที่สายนั้น ๆ ผ่าน 
- หากมีสายอื่นผ่านด้วยให้แสดงเลขสายนั้น ๆ 
- หากไม่มี ไม่ต้องแสดง