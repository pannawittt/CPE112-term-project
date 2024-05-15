# TEST CASE
### main node of our bus stop(s)
![Alt text](src/img/scopes.png)

### to easier understand i'll draw a node on the map the arrow represent the main road that may have the routes

## 1. หา path แบบไม่กำหนดผู้เดินรถ
  - 1.1 src-dest ไม่มีสายไหนผ่าน → ไม่ต้องตอบ
  ### Dynamic of Bus in user's time
  - src-dest ที่เดียวกัน แต่โปรแกรมควรแนะนำให้ใช้เส้นทางที่มีรถในขณะนั้น
  - 1.2 src-dest 1 ต่อ → ตอบสายที่มาก่อน
  
        *input*
        src -> SoiPrachauthit28
        dest -> SoiPrachauthit14
        userTime -> 0408

        *Output*
        21

        *Clarify*
        21 ความถี่ 6.67 นาที/คัน
        75 ความถี่ 4.6 นาที/คัน
        ดังนั้น ... 
  - 1.3 src-dest มีมากกว่า 1 ต่อ → ตอบสายที่ใช้เวลาจาก src-dest รวมถึงเวลารอน้อยกว่าก่อน
  
        *input*
        src -> ThantipBusDepot
        dest -> SoiRatburana18
        userTime -> any

        *Output*
        75 -> WatSarod -> 88

        *Clarify*
        ThantipBusDepot มีแค่ 75
        แล้วเปลี่ยนสายไป 88 ที่ใดก็ได้ในถนนประชาอุทิศแต่ไม่เกินวัดสารอด
  
## 2. หา path แบบกำหนดผู้เดินรถ
  - 2.1 src-dest ไม่มีสายไหนผ่าน → ไม่ต้องตอบ
  - 2.2 src-dest มีสายของบริษัทอื่นผ่าน → ไม่ต้องตอบ
  
        *input*
        src -> SoiPrachauthit51
        dest -> WatSarod
        userTime -> 1500
        BMTA or TSB -> TSB

        *Output*
        -Nothing-

        *Clarify*
        ไม่มี TSB ผ่าน

  - 2.3 src-dest มี 1 สายผ่าน → ตอบสายที่มาก่อน
  
        *input*
        src -> SoiPrachauthit28
        dest -> SoiPrachauthit14
        userTime -> 1500
        BMTA or TSB -> TSB

        *Output*
        75

        *Clarify*
        มี TSB แค่ 75

  - 2.4 src-dest มีมากกว่า 1 สาย → ตอบสายที่ใช้เวลาจาก - src-dest รวมถึงเวลารอน้อยกว่าก่อนโดยที่ต้องเป็นสายที่อยู่ในบริษัทเดียวกัน