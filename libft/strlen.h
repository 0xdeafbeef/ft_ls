/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 20:59:28 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/20 18:07:02 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRLEN_H
# define STRLEN_H
# define ARR if (cp[0] == 0) {return cp - str;} if (cp[1]==0){return cp-str+1;}
# define ARR1 if(cp[2] == 0){return cp-str+2;}if(cp[3]==0){return cp-str+3;}
# define ARR2 if (cp[4]==0){return cp-str+4;}if (cp[5]==0){return cp - str + 5;}
# define ARR3 if (cp[6]==0){return (cp-str+6);}if(cp[7]==0){return (cp-str+7);}
#endif
