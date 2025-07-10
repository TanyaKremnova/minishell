/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkremnov <tkremnov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:46:51 by lperekhr          #+#    #+#             */
/*   Updated: 2025/06/27 10:11:59 by tkremnov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/* signals */
extern volatile sig_atomic_t	g_signal;

void	sigint_handler(int signum);
void	setup_signals(void);
void	setup_child_signals(void);
void	setup_signals_special(void);
void	sigint_interrup(int signum);

/* signal_message */
void	handle_signal_message(int status);

#endif