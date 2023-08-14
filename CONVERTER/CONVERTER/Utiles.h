
#ifndef UTILES_H_
#define UTILES_H_

#define SET_BIT(reg,bit)        (reg|=(1<<bit))
#define CLR_BIT(reg,bit)        (reg&=~(1<<bit))
#define TOG_BIT(reg,bit)        (reg^=(1<<bit))
#define WRITE_BIT(reg,bit,val)  (reg&=(val<<bit))
#define READ_BIT(reg,bit)       ((reg>>bit)&1)



#endif /* UTILES_H_ */